#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "IntroEntity.hpp"
#include "IntroInstruction.hpp"
#include "MovingScene.hpp"

namespace intro{
  namespace moving_scene{
    MovingScene::MovingScene(
        std::string entitiesFilename,
        std::string instructionsFilename,
        std::string soundBufferFilename,
        std::string music,
        sf::Music &player){
      initEntities(entitiesFilename);

    }

    void MovingScene::run(sf::RenderWindow &window){
      window.draw(entities.front().getSprite());
      window.display();
    }

    void  MovingScene::initEntities(std::string &entitiesFilename){
      constexpr int BUFFER_SIZE = 5; 

      std::ifstream entityList(entitiesFilename);
      if(!entityList){
        //Throw IO error 
      }

      //Define a buffer and get the first line containing the
      //number of entities
      std::string buffer[BUFFER_SIZE];
      std::getline(entityList, buffer[0]);
      int size = std::stoi(buffer[0]);

      //test something 
      for(int index = 0; index < size; ++index){
        //Split the line
        for(int buffer_index = 0; buffer_index < BUFFER_SIZE; 
            ++buffer_index){
          std::getline(entityList, buffer[buffer_index], ',');
        }

        //Extract the scale and position of the entity.
        Scale scale(std::stoi(buffer[1]), std::stoi(buffer[2]));
        Position position(std::stoi(buffer[3]), std::stoi(buffer[4]));

        entities.push_back(IntroEntity(buffer[0],scale, position));

      }

      entityList.close();
    }

    void MovingScene::initInstructions(std::string &instructionsFilename){
      constexpr int BUFFER_SIZE = 3; 

      //This has the exception built in according to Prof. Woodring
      std::ifstream instructionList(instructionsFilename);

      //get the number of elements in this list
      std::string buffer[BUFFER_SIZE];
      std::getline(instructionList, buffer[0], ',');
      int size = std::stoi(buffer[0]);

      //throw away the line
      std::getline(instructionList, buffer[0]);

      for(int index = 0; index < size; ++index){
        //Extract the line
        std::getline(instructionList, buffer[0], ',');
        std::getline(instructionList, buffer[1], ',');
        std::getline(instructionList, buffer[2]);

        //Add the element to the vector
        instructions.push_back(IntroInstruction(
              std::stoi(buffer[0]),
              buffer[1], 
              buffer[2]
              )
            );
      }

      instructionList.close();
    }

    void MovingScene::initSounds(std::string &soundBufferList){
      std::ifstream soundList(soundBufferList);
      std::string buffer;

      //Load each buffer and sound file.
      while(std::getline(soundList, buffer)){
        bufferedFiles.push_back(sf::SoundBuffer());
        sounds.push_back(sf::Sound());
        bufferedFiles.back().loadFromFile(buffer);
        sounds.back().setBuffer(bufferedFiles.back());
      }
      soundList.close();
    }

  }
}