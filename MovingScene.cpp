#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/tokenizer.hpp>
#include "csv.h"

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
        sf::Music &player
        ,sf::RenderWindow &rw): window(rw){

      //Load all the components in seperate functions
      initEntities(entitiesFilename);
      initInstructions(instructionsFilename);
      initSounds(soundBufferFilename);

      player.openFromFile(music);

    }

    void MovingScene::run(){
      float nextInstruction = 2.0f;
      float timeElapsed = 0.0f;
      //The ambient wait between the next instruction happening.
      constexpr float AMBIENT_WAIT= 2.0f;
      bool running = true;
      
      sf::Event event;
      sf::Clock timer;

      timer.restart();
      while(running){
        this->window.pollEvent(event);
        this->window.clear();

        //Check to run the next instruction
        if(timeElapsed> nextInstruction){
          float extraWaitTime = doNextInstruction();
          nextInstruction = timer.getElapsedTime().asSeconds() +
            AMBIENT_WAIT + extraWaitTime;
        }
        updateScreen();
        this->window.display();
        running = !instructions.empty();
        timeElapsed = timer.getElapsedTime().asSeconds();
      }
      window.clear();
    }

    void  MovingScene::initEntities(std::string &entitiesFilename){
      std::ifstream entityList(entitiesFilename);

      std::string raw_line;
      std::vector<std::string> data;
      while(std::getline(entityList, raw_line)){
        boost::tokenizer<boost::escaped_list_separator<char>> raw_split
        {raw_line};
        //Put the values inside the vector to be referenced 
        for(const auto &value :raw_split){
          data.push_back(value);
        }

        //Load an entity
        Scale scale(std::stoi(data[1]), std::stoi(data[2]));
        Position position(std::stoi(data[3]), std::stoi(data[4]));

        entities.push_back(IntroEntity(data[0],scale, std::stoi(data[3]), std::stoi(data[4])));
        data.clear();
      }
      entityList.close();
    }

    //TODO make this use csv header
    void MovingScene::initInstructions(std::string &instructionsFilename){
      constexpr int BUFFER_SIZE = 4; 
      std::string buffer[BUFFER_SIZE];

      io::CSVReader<3> lineReader(instructionsFilename);

      while(lineReader.read_row(buffer[0], buffer[1],
            buffer[2])){ 
         instructions.push(IntroInstruction(
              std::stoi(buffer[0]),
              buffer[1], 
              buffer[2]
              )
            );
      }


      //for(int index = 0; index < size; ++index){
        //Extract the line
        //std::getline(instructionList, buffer[0], ',');
        //std::getline(instructionList, buffer[1], ',');
        //std::getline(instructionList, buffer[2]);

        // Add the element to the vector
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

    float MovingScene::doNextInstruction(){
      float addedWait = 0.0f;

      IntroInstruction  &instruction = instructions.front();
      switch(instruction.getAction()){
          case IntroInstruction::MOVE_ENTITY:{
            move_entity(instruction.getEntityID(),
                convertToVec(instruction.getDetail()));
            break;
          }

          case IntroInstruction::SET_POSITION:{
            forcePosition(instruction.getEntityID(),
                convertToVec(instruction.getDetail()));
            break;
          }

          case IntroInstruction::TOGGLE__ENTITY:{
            toggleEntity(instruction.getEntityID());
            break;
          }

          case IntroInstruction::DISPLAY_SPEECH:{
            displaySpeech(instruction.getDetail());
            addedWait = 3.0f;
            break;
          }

          case IntroInstruction::PLAY_SOUND:{
            playSound(convertToInt(instruction.getDetail()));
            break;
          }

          case IntroInstruction::WAIT:{
            addedWait = (float) convertToInt(instruction.getDetail());
            break;
          }
          default: break;
        }  
      instructions.pop();
      return addedWait;
    }

    void MovingScene::move_entity(int entityID, sf::Vector2f  move){
      entities[entityID].moveSprite(move.x, move.y);
    }

    void MovingScene::forcePosition(int entityID, sf::Vector2f position){
      entities[entityID].setPosition(position.x, position.y);
    }

    void MovingScene::toggleEntity(int entityID){
      //Reverse the bool flag on the given entity
      entities[entityID].setEnabled(
          !entities[entityID].isEnabled());
    }

    void MovingScene::displaySpeech(std::string text){
      //Set the Text object
      this->text.setString(text);
      this->text.setCharacterSize(24);

      this->window.draw(this->text);
    }

    void MovingScene::playSound(int soundNumber){
      sounds[soundNumber].play();

    }

    void MovingScene::updateScreen(){
      for(int i = 0; i < entities.size(); ++i){
        if(entities[i].isEnabled()){
          this->window.draw(entities[i].getSprite());
        }
      }
    }

    sf::Vector2f MovingScene::convertToVec(std::string detail){
      std::istringstream strStream(detail);
      std::string splitStr[2];

      //Split the string
      std::getline(strStream, splitStr[0], ' ');
      std::getline(strStream, splitStr[1]);

      return sf::Vector2f(std::stoi(splitStr[0]), std::stoi(splitStr[1]));
    }

    int MovingScene::convertToInt(std::string detail){
      return std::stoi(detail);
    }
  }
}
