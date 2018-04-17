//
//  MainMenuState.hpp
//  EvoSim
//
//  Created by a on 1/26/18.
//  Copyright © 2018 a. All rights reserved.
//

#ifndef MainMenuState_hpp
#define MainMenuState_hpp

#include "State.hpp"

class MainMenuState : public State {
public:
	MainMenuState(StateManager* stateManager);
    ~MainMenuState();
    void processState(sf::Event &event, sf::RenderTarget &renderWindow);
    void updateState(sf::RenderTarget &renderWindow);
    void renderState(sf::RenderTarget &renderWindow);
private:
    sf::Font mainFont;
    sf::Font titleFont;

    sf::Text mainTitle;
    sf::Text titleOne;
    sf::Text titleTwo;
    sf::Text titleThree;

    int buttonSelected;

};

#endif /* MainMenuState_hpp */
