//
//  PauseState.cpp
//  EvoSim
//
//  Created by Vawdrey, Derek on 1/26/18.
//  Copyright © 2018 Vawdrey, Derek. All rights reserved.
//

#include "Headers/PauseState.hpp"

PauseState::PauseState(StateManager* stateManager){
	this->stateManager = stateManager;
}


PauseState::~PauseState(){
    
}

void PauseState::processState(sf::Event &event, sf::RenderTarget &renderWindow){
    if(event.type == sf::Event::MouseButtonPressed){
        
    }
}
void PauseState::updateState(sf::RenderTarget &renderWindow){
    
}
void PauseState::renderState(sf::RenderTarget &renderWindow){
    
    
}
