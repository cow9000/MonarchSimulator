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
	this->minHappiness = 80 + (population/5);


	this->defaultFont.loadFromFile("Assets/Fonts/trench100free.ttf");

	popText.setFont(defaultFont);
	happinessText.setFont(defaultFont);
	goldText.setFont(defaultFont);

	popText.setFillColor(sf::Color::White);
	happinessText.setFillColor(sf::Color::White);
	goldText.setFillColor(sf::Color::White);

	popText.setCharacterSize(20);
	happinessText.setCharacterSize(20);
	goldText.setCharacterSize(20);



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
	popText.setString("Population:   " + std::to_string(population));
	happinessText.setString("Happiness:   " + std::to_string(happiness));
	goldText.setString("Gold:   " + std::to_string(gold));

	popText.setPosition(30, renderWindow.getSize().y-150);
	happinessText.setPosition(30, renderWindow.getSize().y-100);
	goldText.setPosition(30, renderWindow.getSize().y-50);
}
void PlayState::renderState(sf::RenderTarget &renderWindow){
    //Render GUI
	drawGUI(renderWindow);
}

void PlayState::drawGUI(sf::RenderTarget &renderWindow){
	renderWindow.draw(popText);
	renderWindow.draw(happinessText);
	renderWindow.draw(goldText);
}


void PlayState::startOfDay(){

}

void PlayState::endOfDay(){
	//POPULATION ADD
	this->minHappiness = 80 + (population/5);

	int happinessAdd = happiness - minHappiness;
	if(happinessAdd > 50) happinessAdd = 50;
	else if(happinessAdd < -50) happinessAdd = -50;

	population += minHappiness;
	///////////////////////////

}
