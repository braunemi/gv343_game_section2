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
        Help(sf::RenderWindow &window);

        int show();

    private:
        void processEvents();

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
