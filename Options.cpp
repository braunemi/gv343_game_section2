//
// Created by crk on 10/6/2018.
//
#include <iostream>
#include <Settings.hpp>
#include <Animator.hpp>
#include "Options.hpp"
#include "SFML/Audio.hpp"

namespace options {
    Options::Options(sf::RenderWindow &rw) : window(rw) {

    }

    int Options::show() {
        this->window.clear();
        sf::Texture splash;
        if(!splash.loadFromFile("./images/neighborhood.png")){
            std::cerr << "Can't load start image." << std::endl;
        }
        sf::Sprite sprite;
        sprite.setTexture(splash);

        sf::Font font;
        if(!font.loadFromFile("fonts/Notable-Regular.ttf")){
            return EXIT_FAILURE;
        }

        sf::Text title;
        title.setFont(font);
        title.setString("Options");
        title.setCharacterSize(48);
        title.setFillColor(sf::Color::White);
        title.setPosition(250,10);

        sf::Text text;
        text.setFont(font);
        text.setString("(Press Enter to continue)");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(150, 350);

        sf::Clock clock;

        sf::Music music;
        if(!music.openFromFile("music/epic_hero.wav")){
            return EXIT_FAILURE;
        }

        music.play();
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    window.close();
                    music.stop();
                    exit(0);
                }

                if(event.type == sf::Event::KeyPressed){
                    if(event.key.code == sf::Keyboard::Return){
                        window.clear();
                        music.stop();
                        return 0;
                    }
                }

            }

            window.draw(sprite);
            window.draw(title);
            window.draw(text);
            window.display();
        }
        return 0;
    }

}

