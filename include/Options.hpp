//
// Created by crk on 10/6/2018.
//

#ifndef CIS_343_02_OPTIONS_HPP
#define CIS_343_02_OPTIONS_HPP
#include "SFML/Graphics.hpp"
#include <string>

namespace options {
    class Options {
    public:
        sf::RenderWindow& window;
        Options() = default;
        explicit Options(sf::RenderWindow& rw);
        ~Options() = default;
        int show();
    };
} // namespace options
#endif //CIS_343_02_OPTIONS_HPP
