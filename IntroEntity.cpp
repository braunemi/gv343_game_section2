#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "IntroEntity.hpp"

namespace intro{
  namespace moving_scene{
    IntroEntity::IntroEntity(
        std::string filename, 
        Scale scale, 
        int x, int y){

      if(!texture.loadFromFile(filename)){
        std::cout << "failure on texture" << std::endl;
      }

      //Set sprite's texture, scale, and starting position
      sprite.setTexture(texture);
      sprite.setScale(scale.x, scale.y);
      sprite.setPosition(x, y);

      sf::Vector2f position = sprite.getPosition();

      std::cout << position.x <<" " << position.y << std::endl;

      this->scale = scale;
    }

    sf::Sprite IntroEntity::getSprite(){
      this->sprite.setTexture(texture);
      return this->sprite;
    }

    void IntroEntity::moveSprite(int deltaX, int deltaY){
      if(deltaX > 0 || deltaX < 0){
        sprite.setScale(-scale.x, scale.y);
      }
      sprite.setPosition(x+deltaX, y+deltaY);
    }

    void IntroEntity::setPosition(int x, int y){
      sprite.setPosition(x,y);
    }
  } 
}
