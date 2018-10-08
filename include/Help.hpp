//
// Created by Matt Tetreau on 10/7/2018.
//

#ifndef        HELP
#define        HELP

#include "Collision.hpp"
#include "Game.hpp"
#include "Person.hpp"
#include "Monster.hpp"
#include "Settings.hpp"
#include <iostream>
#include <random>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

namespace help {
    class Help {
    public:
        /**************************************************
        *Default constructor
        **************************************************/
        Help(sf::RenderWindow &window);
        /**************************************************
        *Displays the options menu and controls
        *@return int 0
        **************************************************/
        int show();
    private:
        sf::Text title;
        sf::Text up;
        sf::Text down;
        sf::Text left;
        sf::Text right;
        sf::Font font;
        sf::RenderWindow &window;
        sf::Music music;
        sf::Texture splash;
        sf::Sprite sprite;
    };
}

#endif