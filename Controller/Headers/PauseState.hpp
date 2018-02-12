//
//  PauseState.hpp
//  EvoSim
//
//  Created by Vawdrey, Derek on 1/26/18.
//  Copyright © 2018 Vawdrey, Derek. All rights reserved.
//

#ifndef PauseState_hpp
#define PauseState_hpp

#include "State.hpp"

class PauseState : public State {
public:
	PauseState(StateManager* stateManager);
    ~PauseState();
    void processState(sf::Event &event, sf::RenderTarget &renderWindow);
    void updateState(sf::RenderTarget &renderWindow);
    void renderState(sf::RenderTarget &renderWindow);
};

#endif /* PauseState_hpp */
