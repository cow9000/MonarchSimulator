//
//  OptionsMenuState.hpp
//  EvoSim
//
//  Created by a on 1/26/18.
//  Copyright © 2018 a. All rights reserved.
//

#ifndef OptionsMenuState_hpp
#define OptionsMenuState_hpp

#include "State.hpp"

class OptionsMenuState : public State {
public:
	OptionsMenuState(StateManager* stateManager);
    ~OptionsMenuState();
    void processState(sf::Event &event, sf::RenderTarget &renderWindow);
    void updateState(sf::RenderTarget &renderWindow);
    void renderState(sf::RenderTarget &renderWindow);
};
#endif /* OptionsMenuState_hpp */
