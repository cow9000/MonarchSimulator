//
//  PlayState.cpp
//  EvoSim
//
//  Created by Vawdrey, Derek on 1/26/18.
//  Copyright © 2018 Vawdrey, Derek. All rights reserved.
//

#include "Headers/PlayState.hpp"
#include <iostream>

PlayState::PlayState(StateManager* stateManager){
	this->stateManager = stateManager;
	this->changeWindowSize = false;

	this->population = 100;
	this->happiness = 100;
	this->gold = 200;
    
}


PlayState::~PlayState(){
    
}

void PlayState::processState(sf::Event &event, sf::RenderTarget &renderWindow){
    if(event.type == sf::Event::MouseButtonPressed){
        
    }else if(event.type == sf::Event::Resized){
    	renderWindow.setView(sf::View(sf::FloatRect(0.f,0.f,event.size.width,event.size.height)));

    }
}
void PlayState::updateState(sf::RenderTarget &renderWindow){

}
void PlayState::renderState(sf::RenderTarget &renderWindow){
    
}
