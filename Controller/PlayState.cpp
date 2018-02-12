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
    this->fillChunks = true;
    
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
    if(fillChunks){
        for(int x = 0; x < renderWindow.getSize().x/GameManager::chunkSize.x; x+=2){
            for(int y = 0; y < renderWindow.getSize().y/GameManager::chunkSize.y; y+=2){
                chunks.push_back(new Chunk(sf::Vector2f(x,y)));
            }
        }
        fillChunks = false;
    }



}
void PlayState::renderState(sf::RenderTarget &renderWindow){
    
    for(int i = 0; i < chunks.size(); i++){
    	chunks.at(i)->updateChunk();
    	std::cout << "Chunk drawn" << std::endl;
    	renderWindow.draw(*chunks.at(i));

    }

    
}
