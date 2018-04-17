//
//  PlayState.hpp
//  EvoSim
//
//  Created by a on 1/26/18.
//  Copyright © 2018 a. All rights reserved.
//

#ifndef PlayState_hpp
#define PlayState_hpp


#include <SFML/Audio.hpp>
#include <iostream>
#include "Gameplay/GameManager.hpp"
#include "State.hpp"
#include "Gameplay/NPCManager.hpp"
#include "Gameplay/Block.hpp"


class PlayState : public State {
public:
	PlayState(StateManager* stateManager);
    ~PlayState();
    void processState(sf::Event &event, sf::RenderTarget &renderWindow);
    void updateState(sf::RenderTarget &renderWindow);
    void renderState(sf::RenderTarget &renderWindow);
    Json::Value& returnGameSaveData();
private:

	sf::Texture goldPositive;
	sf::Texture goldNegative;
	sf::Texture happinessPositive;
	sf::Texture happinessNegative;
	sf::Texture populationPositive;
	sf::Texture populationNegative;


    void startOfDay();
    void endOfDay();
    bool dayEnd;

    //Rendering
    void drawGUI(sf::RenderTarget &renderWindow);
    void drawBackground(sf::RenderTarget &renderWindow);
    void drawNPC(sf::RenderTarget &renderWindow);

    bool changeWindowSize;
    bool showYesOrNo;
    bool chosenYes;
    bool chosenNo;
    bool haveSentChosenSignal;
    //Rotate 15 then rotate to -15
    bool backwards;
    int rotateYesOrNo;


    sf::Clock addedTimer;
    std::vector<Block*> movingBlocks;

    //dusk/night
    bool isDusk;
    bool isNight;

    sf::Sprite yes;
    sf::Sprite no;
    sf::Sprite yesOrNo;

    int population;
    int happiness;
    int gold;

    NPCManager* manager;

    int minHappiness;

    sf::Text popText;
    sf::Text happinessText;
    sf::Text goldText;

    sf::Font defaultFont;

    sf::Sprite cloud1;
    sf::Sprite cloud2;
    sf::Sprite cloud3;
    sf::Sprite cloud4;
    sf::Sprite cloud5;
    sf::Sprite cloud6;

    sf::Sprite King;
    //Yes or no = Soundbuffer1
    sf::SoundBuffer soundBuffer1;
    sf::Sound sound1;


    sf::SoundBuffer soundBuffer2;
    sf::Sound sound2;

    sf::SoundBuffer soundBuffer3;
    sf::Sound sound3;

    Json::Value GameSaveData;

};

#endif /* PlayState_hpp */
