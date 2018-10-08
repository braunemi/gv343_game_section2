//
// Created by Matt Tetreau on 10/7/2018.
//

#include "Collision.hpp"
#include "Game.hpp"
#include "Person.hpp"
#include "Monster.hpp"
#include "Settings.hpp"
#include <iostream>
#include <random>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "Help.hpp"

namespace help {
    Help::Help(sf::RenderWindow &rw) : window(rw) {

    }

    int Help::show() {
        this->window.clear();
        sf::Texture splash;
        if (!splash.loadFromFile("./images/House.png")) {
            std::cerr << "Can't load start image." << std::endl;
        }
        sf::Sprite sprite;
        sprite.setTexture(splash);
        sf::Font font;
        if (!font.loadFromFile("fonts/Notable-Regular.ttf")) {
            return EXIT_FAILURE;
        }

        sf::Music music;
        if (!music.openFromFile("music/epic_hero.wav")) {
            return EXIT_FAILURE;
        }
        music.play();

        sf::Text title;
        title.setFont(font);
        title.setString("Controls");
        title.setCharacterSize(48);
        title.setFillColor(sf::Color::White);
        title.setPosition(260, 10);

        sf::Text up;
        up.setFont(font);
        up.setString("Move Up ..... Up Arrow");
        up.setCharacterSize(24);
        up.setFillColor(sf::Color::White);
        up.setPosition(100, 100);

        sf::Text down;
        down.setFont(font);
        down.setString("Move Down ..... Down Arrow");
        down.setCharacterSize(24);
        down.setFillColor(sf::Color::White);
        down.setPosition(100, 150);

        sf::Text left;
        left.setFont(font);
        left.setString("Move Left ..... Left Arrow");
        left.setCharacterSize(24);
        left.setFillColor(sf::Color::White);
        left.setPosition(100, 200);

        sf::Text right;
        right.setFont(font);
        right.setString("Move Right ..... Right Arrow");
        right.setCharacterSize(24);
        right.setFillColor(sf::Color::White);
        right.setPosition(100, 250);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    music.stop();
                    exit(0);
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::O) {
                        window.clear();
                        return 0;
                    }
                }
            }
            window.draw(sprite);
            window.draw(title);
            window.draw(up);
            window.draw(down);
            window.draw(left);
            window.draw(right);

            window.display();
        }
        return 0;
    }
}