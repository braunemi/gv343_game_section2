//
// Created by crk on 10/6/2018.
//
#include <iostream>
#include <Settings.hpp>
#include <Animator.hpp>
#include "Options.hpp"
#include "SFML/Audio.hpp"
#include "Help.hpp"
#include "Credits.hpp"

namespace options {
    Options::Options(sf::RenderWindow &rw) : window(rw) {

    }

    int Options::show() {
        this->window.clear();
        sf::Texture splash;
        if(!splash.loadFromFile("./images/House.png")){
            std::cerr << "Can't load start image." << std::endl;
        }
        sf::Sprite sprite;
        sprite.setTexture(splash);

        sf::Font font;
        if(!font.loadFromFile("fonts/Notable-Regular.ttf")){
            return EXIT_FAILURE;
        }

        //Text for title
        sf::Text title;
        title.setFont(font);
        title.setString("Options");
        title.setCharacterSize(48);
        title.setFillColor(sf::Color::White);
        title.setPosition(260,10);

        //Text for Music control
        sf::Text sound;
        sound.setFont(font);
        sound.setString("- & +: Music volume");
        sound.setCharacterSize(24);
        sound.setFillColor(sf::Color::White);
        sound.setPosition(100, 100);

        //Text for Sound FX control
        sf::Text sfx;
        sfx.setFont(font);
        sfx.setString("< & >: SoundFX volume");
        sfx.setCharacterSize(24);
        sfx.setFillColor(sf::Color::White);
        sfx.setPosition(100, 150);
        sf::Text highScore;

        //Text for High Score
        highScore.setFont(font);
        highScore.setString("S: High Scores");
        highScore.setCharacterSize(24);
        highScore.setFillColor(sf::Color::White);
        highScore.setPosition(100, 200);

        //Text for Credits
        sf::Text credits;
        credits.setFont(font);
        credits.setString("C: Credits");
        credits.setCharacterSize(24);
        credits.setFillColor(sf::Color::White);
        credits.setPosition(100, 250);

        //Text for Help menu
        sf::Text help;
        help.setFont(font);
        help.setString("H: Help");
        help.setCharacterSize(24);
        help.setFillColor(sf::Color::White);
        help.setPosition(100, 300);

        //Text for return to main menu
        sf::Text menu;
        menu.setFont(font);
        menu.setString("M: Main Menu");
        menu.setCharacterSize(24);
        menu.setFillColor(sf::Color::White);
        menu.setPosition(100, 450);

        sf::Clock clock;

        sf::Music music;
        if(!music.openFromFile("music/epic_hero.wav")){
            return EXIT_FAILURE;
        }

        music.play();
        while (window.isOpen())
        {
            //Event handler
            sf::Event event;
            while (window.pollEvent(event))
            {
                //Handle window closing
                if (event.type == sf::Event::Closed){
                    window.close();
                    music.stop();
                    exit(0);
                }

                //Handle key press
                if(event.type == sf::Event::KeyPressed){
                    //Returns to main menu when M is pressed
                    if(event.key.code == sf::Keyboard::M){
                        window.clear();
                        return 0;
                    }
                    if(event.key.code == sf::Keyboard::Hyphen){

                    }
                    if(event.key.code == sf::Keyboard::Equal){

                    }
                    if(event.key.code == sf::Keyboard::Comma){

                    }
                    if(event.key.code == sf::Keyboard::Period){

                    }
                    if(event.key.code == sf::Keyboard::S){

                    }
                    //Starts the credits when C is pressed
                    if(event.key.code == sf::Keyboard::C){
                        Credits c;
                        c.start(window);
                        window.clear();
                    }
                    // Goes to help menu when H is pressed
                    if(event.key.code == sf::Keyboard::H){
                        help::Help h (window);
                        h.show();
                        window.clear();
                    }
                }
            }

            //display everything
            window.draw(sprite);
            window.draw(title);
            window.draw(sound);
            window.draw(sfx);
            window.draw(highScore);
            window.draw(credits);
            window.draw(help);
            //window.draw(difficulty);
            window.draw(menu);

            window.display();
        }
        return 0;
    }
}

