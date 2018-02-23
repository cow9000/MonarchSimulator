//
//  PlayState.hpp
//  EvoSim
//
//  Created by Vawdrey, Derek on 1/26/18.
//  Copyright © 2018 Vawdrey, Derek. All rights reserved.
//

#ifndef PlayState_hpp
#define PlayState_hpp

#include "State.hpp"

class PlayState : public State {
public:
	PlayState(StateManager* stateManager);
    ~PlayState();
    void processState(sf::Event &event, sf::RenderTarget &renderWindow);
    void updateState(sf::RenderTarget &renderWindow);
    void renderState(sf::RenderTarget &renderWindow);
private:
    void startOfDay();
    void endOfDay();

    //Rendering
    void drawGUI(sf::RenderTarget &renderWindow);
    void drawBackground(sf::RenderTarget &renderWindow);
    void drawNPC(sf::RenderTarget &renderWindow);

    bool changeWindowSize;
    bool showYesOrNo;
    bool chosenYes;
    bool chosenNo;
    //Rotate 15 then rotate to -15
    bool backwards;
    int rotateYesOrNo;

    sf::Sprite yes;
    sf::Sprite no;
    sf::Sprite yesOrNo;

    int population;
    int happiness;
    int gold;

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

};

#endif /* PlayState_hpp */
