//
//  OptionsMenuState.cpp
//  EvoSim
//
//  Created by Vawdrey, Derek on 1/26/18.
//  Copyright © 2018 Vawdrey, Derek. All rights reserved.
//

#include "Headers/OptionsMenuState.hpp"

OptionsMenuState::OptionsMenuState(StateManager* stateManager){
	this->stateManager = stateManager;
}


OptionsMenuState::~OptionsMenuState(){
    
}

void OptionsMenuState::processState(sf::Event &event, sf::RenderTarget &renderWindow){
    if(event.type == sf::Event::MouseButtonPressed){
        
    }
}
void OptionsMenuState::updateState(sf::RenderTarget &renderWindow){
    
}
void OptionsMenuState::renderState(sf::RenderTarget &renderWindow){
    
    
}
