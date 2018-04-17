//
//  PlayState.cpp
//  EvoSim
//
//  Created by a on 1/26/18.
//  Copyright © 2018 a. All rights reserved.
//

#include "Headers/SplashState.hpp"
#include "Headers/StateManager.hpp"
#include <iostream>

SplashState::SplashState(StateManager* stateManager){
	this->stateManager = stateManager;
	this->wait = true;
	this->timePassed = 0;

	logoTexture.loadFromFile("Assets/Logo.png");
}

SplashState::~SplashState(){
    
}

void SplashState::processState(sf::Event &event, sf::RenderTarget &renderWindow){
    if(event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::TextEntered){
    	stateManager->setCurrentState(States::implementedStates::MAINMENU);
    }else if(event.type == sf::Event::Resized){
    	renderWindow.setView(sf::View(sf::FloatRect(0.f,0.f,event.size.width,event.size.height)));
    }
}

void SplashState::updateState(sf::RenderTarget &renderWindow){
    //If timePassed is creater than 255 + 60
	if(timePassed >= 255){
		stateManager->setCurrentState(States::implementedStates::MAINMENU);
	}

	if(splashClock.getElapsedTime().asSeconds() > 1 && wait){
		wait = false;
		splashClock.restart();
	}

}

void SplashState::renderState(sf::RenderTarget &renderWindow){

	//Draw logo
	sf::Sprite logo(logoTexture);
	sf::FloatRect logoRect = logo.getLocalBounds();

	logo.setOrigin(logoRect.left + logoRect.width/2.0f, logoRect.top  + logoRect.height/2.0f);
	logo.setPosition(renderWindow.getSize().x/2,renderWindow.getSize().y/2);
	renderWindow.draw(logo);

	if(wait == false){
		sf::RectangleShape splashColor;
		splashColor.setSize(sf::Vector2f(renderWindow.getSize().x, renderWindow.getSize().y));

		timePassed = splashClock.getElapsedTime().asSeconds() * 350;

		sf::Color splashFade(0,0,0,timePassed);


		if(timePassed >= 255){
			splashFade.a = 255;
		}

		splashColor.setFillColor(splashFade);
		splashColor.setPosition(0,0);
		renderWindow.draw(splashColor);
	}
    
}
