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


	this->defaultFont.loadFromFile("Assets/Fonts/GameFont.ttf");

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
	popText.setString(std::to_string(population));
	happinessText.setString(std::to_string(happiness));
	goldText.setString(std::to_string(gold));

	popText.setPosition(70, renderWindow.getSize().y-150);
	happinessText.setPosition(70, renderWindow.getSize().y-100);
	goldText.setPosition(70, renderWindow.getSize().y-50);
}
void PlayState::renderState(sf::RenderTarget &renderWindow){

	//Draw background stuff
	drawBackground(renderWindow);

	//Draw NPCs
	drawNPC(renderWindow);

    //Render GUI
	drawGUI(renderWindow);
}

void PlayState::drawNPC(sf::RenderTarget &renderWindow){

}

void PlayState::drawBackground(sf::RenderTarget &renderWindow){

	sf::Texture skyBackground;
	skyBackground.loadFromFile("Assets/Gameplay/Sky.png");
	sf::Sprite skyback(skyBackground);
	skyback.setScale(2.0,2.0);
	renderWindow.draw(skyback);



	sf::Texture background1Texture;
	background1Texture.loadFromFile("Assets/Gameplay/BackgroundHills.png");
	sf::Sprite background1(background1Texture);

	background1.setPosition(0, renderWindow.getSize().y - background1.getLocalBounds().height);

	renderWindow.draw(background1);


	//Draw game stuff
	sf::Texture kingTexture;
	kingTexture.loadFromFile("Assets/Gameplay/King.png");

	sf::Sprite kingSprite(kingTexture);
	kingSprite.setPosition(0, renderWindow.getSize().y - kingSprite.getLocalBounds().height);

	renderWindow.draw(kingSprite);
}

void PlayState::drawGUI(sf::RenderTarget &renderWindow){


	sf::Texture GuiTexture;
	GuiTexture.loadFromFile("Assets/Gameplay/GuiBackground.png");

	sf::Sprite GuiSprite(GuiTexture);
	GuiSprite.setPosition(0,renderWindow.getSize().y-GuiSprite.getLocalBounds().height-10);

	renderWindow.draw(GuiSprite);


	sf::Texture happinessTexture;
	sf::Texture populationTexture;
	sf::Texture goldTexture;

	happinessTexture.loadFromFile("Assets/Gameplay/Happiness.png");
	populationTexture.loadFromFile("Assets/Gameplay/Population.png");
	goldTexture.loadFromFile("Assets/Gameplay/Gold.png");

	sf::Sprite goldSprite(goldTexture);
	goldSprite.setPosition(30, goldText.getPosition().y - 5);
	sf::Sprite populationSprite(populationTexture);
	populationSprite.setPosition(30, popText.getPosition().y - 5 );
	sf::Sprite happinessSprite(happinessTexture);
	happinessSprite.setPosition(30, happinessText.getPosition().y - 5);

	renderWindow.draw(goldSprite);
	renderWindow.draw(populationSprite);
	renderWindow.draw(happinessSprite);
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
