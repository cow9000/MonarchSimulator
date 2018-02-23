//
//  MainMenuState.cpp
//  EvoSim
//
//  Created by Vawdrey, Derek on 1/26/18.
//  Copyright © 2018 Vawdrey, Derek. All rights reserved.
//

#include "Headers/MainMenuState.hpp"
#include "Headers/StateManager.hpp"
#include "Headers/Gameplay/GameManager.hpp"
#include <cmath>
#include <iostream>

MainMenuState::MainMenuState(StateManager* stateManager){
	this->stateManager = stateManager;
	this->mainFont.loadFromFile("Assets/Fonts/GameFont.ttf");
	this->titleFont.loadFromFile("Assets/Fonts/GameFont.ttf");
	this->buttonSelected = 0;

	mainTitle.setString("Kingdom Simulator");
	mainTitle.setCharacterSize(64);
	mainTitle.setFont(titleFont);

	sf::FloatRect textRect = mainTitle.getLocalBounds();
	mainTitle.setOrigin(std::round(textRect.left + textRect.width/2.0f), std::round(textRect.top  + textRect.height/2.0f));

	titleOne.setString("Start Game");
	titleTwo.setString("Options");
	titleThree.setString("Quit");

	titleOne.setCharacterSize(48);
	titleTwo.setCharacterSize(48);
	titleThree.setCharacterSize(48);

	titleOne.setFont(mainFont);
	titleTwo.setFont(mainFont);
	titleThree.setFont(mainFont);

	textRect = titleOne.getLocalBounds();
	titleOne.setOrigin(std::round(textRect.left + textRect.width/2.0f), std::round(textRect.top  + textRect.height/2.0f));

	textRect = titleTwo.getLocalBounds();
	titleTwo.setOrigin(std::round(textRect.left + textRect.width/2.0f), std::round(textRect.top  + textRect.height/2.0f));

	textRect = titleThree.getLocalBounds();
	titleThree.setOrigin(std::round(textRect.left + textRect.width/2.0f), std::round(textRect.top  + textRect.height/2.0f));

}

MainMenuState::~MainMenuState(){
    
}

void MainMenuState::processState(sf::Event &event, sf::RenderTarget &renderWindow){
    if(event.type == sf::Event::MouseButtonPressed){
        if(buttonSelected > 0){
        	if(buttonSelected == 1){
        		stateManager->setCurrentState(States::implementedStates::PLAY);
        	}else if(buttonSelected == 2){
        		//stateManager->setCurrentState(States::implementedStates::OPTIONS);
        	}else if(buttonSelected == 3){

        	}
        }
    }else if(event.type == sf::Event::MouseMoved){
    	buttonSelected = 0;
    	for(int i = 0; i < 1; i++){
    		sf::FloatRect buttonArea;
    		if(i == 0){
    			buttonArea = titleOne.getGlobalBounds();
    		}else if(i == 1){
    			//buttonArea = titleTwo.getGlobalBounds();
    		}else if(i == 2){
    			//buttonArea = titleThree.getGlobalBounds();
    		}



    		if(buttonArea.contains(event.mouseMove.x,event.mouseMove.y)){
    			buttonSelected = i+1;
    		}

    	}
    }
    else if(event.type == sf::Event::Resized){
    	renderWindow.setView(sf::View(sf::FloatRect(0.f,0.f,event.size.width,event.size.height)));
    }
}
void MainMenuState::updateState(sf::RenderTarget &renderWindow){
	mainTitle.setPosition(std::round(renderWindow.getSize().x/2),50);
	titleOne.setPosition(std::round(renderWindow.getSize().x/2),std::round(renderWindow.getSize().y/2));
	//titleTwo.setPosition(std::round(renderWindow.getSize().x/2),250);
	//titleThree.setPosition(std::round(renderWindow.getSize().x/2),350);

	//Set button colors
	titleOne.setFillColor(GameManager::buttonUnSelectedColor);
	titleTwo.setFillColor(GameManager::buttonUnSelectedColor);
	titleThree.setFillColor(GameManager::buttonUnSelectedColor);


	if(buttonSelected > 0){

		if(buttonSelected == 1){
			titleOne.setFillColor(GameManager::buttonSelectedColor);
		}else if(buttonSelected == 2){
			titleTwo.setFillColor(GameManager::buttonSelectedColor);
		}else if(buttonSelected == 3){
			titleThree.setFillColor(GameManager::buttonSelectedColor);
		}
	}

}
void MainMenuState::renderState(sf::RenderTarget &renderWindow){


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
	sf::Sprite King;
	King.setTexture(kingTexture);
	King.setPosition(0, renderWindow.getSize().y - King.getLocalBounds().height);

	renderWindow.draw(King);

	sf::Texture overlay;
	overlay.loadFromFile("Assets/Gameplay/Night.png");
	sf::Sprite overlaySprite;
	overlaySprite.setTexture(overlay);
	sf::Vector2u targetSize = renderWindow.getSize();

	overlaySprite.setScale(
		targetSize.x / overlaySprite.getLocalBounds().width,
		targetSize.y / overlaySprite.getLocalBounds().height);

	renderWindow.draw(overlaySprite);


	renderWindow.draw(mainTitle);
    renderWindow.draw(titleOne);
    //renderWindow.draw(titleTwo);
    //renderWindow.draw(titleThree);
}
