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
    //Default constructor
    Help::Help(sf::RenderWindow &rw) : window(rw) {

    }
    /***************************************************************
    *Displays the help menu and controls
    *@return int 0
    ***************************************************************/
    int Help::show() {
        //Loads the background
        this->window.clear();
        sf::Texture splash;
        if (!splash.loadFromFile("./images/House.png")) {
            std::cerr << "Can't load start image." << std::endl;
        }

        //Sets texture
        sf::Sprite sprite;
        sprite.setTexture(splash);
        sf::Font font;
        if (!font.loadFromFile("fonts/Notable-Regular.ttf")) {
            return EXIT_FAILURE;
        }

        //Opens and plays the music
        sf::Music music;
        if (!music.openFromFile("music/epic_hero.wav")) {
            return EXIT_FAILURE;
        }
        music.play();

        //Controls header
        sf::Text title;
        title.setFont(font);
        title.setString("Controls");
        title.setCharacterSize(48);
        title.setFillColor(sf::Color::White);
        title.setPosition(260, 10);

        //Controls for move up
        sf::Text up;
        up.setFont(font);
        up.setString("Move Up ..... Up Arrow");
        up.setCharacterSize(24);
        up.setFillColor(sf::Color::White);
        up.setPosition(100, 100);

        //Controls for move down
        sf::Text down;
        down.setFont(font);
        down.setString("Move Down ..... Down Arrow");
        down.setCharacterSize(24);
        down.setFillColor(sf::Color::White);
        down.setPosition(100, 150);

        //Controls for move left
        sf::Text left;
        left.setFont(font);
        left.setString("Move Left ..... Left Arrow");
        left.setCharacterSize(24);
        left.setFillColor(sf::Color::White);
        left.setPosition(100, 200);

        //Controls for move right
        sf::Text right;
        right.setFont(font);
        right.setString("Move Right ..... Right Arrow");
        right.setCharacterSize(24);
        right.setFillColor(sf::Color::White);
        right.setPosition(100, 250);

        //Event handling
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                //Closes the program
                if (event.type == sf::Event::Closed) {
                    window.close();
                    music.stop();
                    exit(0);
                }
                //Return to options menu
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::O) {
                        window.clear();
                        return 0;
                    }
                }
            }

            //Draws the help window
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