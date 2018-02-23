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

	cloud1.setPosition(rand()%1500,rand()%1500);
	cloud2.setPosition(rand()%1500,rand()%1500);
	cloud3.setPosition(rand()%1500,rand()%1500);

	cloud4.setPosition(rand()%1500,rand()%1500);
	cloud5.setPosition(rand()%1500,rand()%1500);
	cloud6.setPosition(rand()%1500,rand()%1500);

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

	this->showYesOrNo = true;
	this->chosenYes = false;
	this->chosenNo = false;
	this->rotateYesOrNo = 0;
	this->backwards = false;

	this->isDusk = false;
	this->isNight = true;

}


PlayState::~PlayState(){
    
}

void PlayState::processState(sf::Event &event, sf::RenderTarget &renderWindow){
    if(event.type == sf::Event::MouseButtonPressed){
        
    }else if(event.type == sf::Event::Resized){
    	renderWindow.setView(sf::View(sf::FloatRect(0.f,0.f,event.size.width,event.size.height)));

    }else if(event.type == sf::Event::KeyPressed){
    	if(event.key.code == sf::Keyboard::Y){
    		if(showYesOrNo){
    			if(!chosenYes && !chosenNo){
    				chosenYes = true;
    			}
    		}
    	}else if(event.key.code == sf::Keyboard::N){
    		if(showYesOrNo){
				if(!chosenYes && !chosenNo){
					chosenNo = true;
				}
			}
    	}
    }
}
void PlayState::updateState(sf::RenderTarget &renderWindow){
	popText.setString(std::to_string(population));
	happinessText.setString(std::to_string(happiness));
	goldText.setString(std::to_string(gold));

	popText.setPosition(70, renderWindow.getSize().y-150);
	happinessText.setPosition(70, renderWindow.getSize().y-100);
	goldText.setPosition(70, renderWindow.getSize().y-50);

	if(isDusk){
		isNight = false;
	}else if(isNight){
		isDusk = false;
	}


}
void PlayState::renderState(sf::RenderTarget &renderWindow){

	//Draw background stuff
	drawBackground(renderWindow);

	//Draw NPCs
	drawNPC(renderWindow);

    //Render GUI
	drawGUI(renderWindow);




	//Draw dusk/night
	if(isDusk){
		sf::Texture overlay;
		overlay.loadFromFile("Assets/Gameplay/Dusk.png");
		sf::Sprite overlaySprite;
		overlaySprite.setTexture(overlay);
		sf::Vector2u targetSize = renderWindow.getSize();

		overlaySprite.setScale(
		    targetSize.x / overlaySprite.getLocalBounds().width,
		    targetSize.y / overlaySprite.getLocalBounds().height);

		renderWindow.draw(overlaySprite);
	}else if(isNight){
		sf::Texture overlay;
		overlay.loadFromFile("Assets/Gameplay/Night.png");
		sf::Sprite overlaySprite;
		overlaySprite.setTexture(overlay);
		sf::Vector2u targetSize = renderWindow.getSize();

		overlaySprite.setScale(
		    targetSize.x / overlaySprite.getLocalBounds().width,
		    targetSize.y / overlaySprite.getLocalBounds().height);

		renderWindow.draw(overlaySprite);
	}


}

void PlayState::drawNPC(sf::RenderTarget &renderWindow){

	if(showYesOrNo){
		sf::Texture yesNoTexture;
		if(chosenYes){
			yesNoTexture.loadFromFile("Assets/Gameplay/Yes.png");
		}else if(chosenNo){
			yesNoTexture.loadFromFile("Assets/Gameplay/No.png");
		}else{
			yesNoTexture.loadFromFile("Assets/Gameplay/YesOrNo.png");
		}
		yesOrNo.setTexture(yesNoTexture);

		yesOrNo.setPosition(King.getLocalBounds().width-50, King.getPosition().y+100);

		yesOrNo.setRotation(rotateYesOrNo);

		if(backwards){
			rotateYesOrNo -= 1;
		}else{
			rotateYesOrNo += 1;
		}

		if(rotateYesOrNo > 5 || rotateYesOrNo < -5){

			backwards = !backwards;
		}

		renderWindow.draw(yesOrNo);
	}
}

void PlayState::drawBackground(sf::RenderTarget &renderWindow){


	sf::Texture skyBackground;
	skyBackground.loadFromFile("Assets/Gameplay/Sky.png");
	sf::Sprite skyback(skyBackground);
	skyback.setScale(2.0,2.0);
	renderWindow.draw(skyback);


	//Draw clouds

	if(cloud1.getPosition().x > renderWindow.getSize().x){
		cloud1.setPosition(-rand()%500,rand()%500);
	}

	if(cloud2.getPosition().x > renderWindow.getSize().x){
		cloud2.setPosition(-rand()%500,rand()%500);
	}

	if(cloud3.getPosition().x > renderWindow.getSize().x){
		cloud3.setPosition(-rand()%500,rand()%500);
	}

	if(cloud4.getPosition().x > renderWindow.getSize().x){
		cloud4.setPosition(-rand()%500,rand()%500);
	}

	if(cloud5.getPosition().x > renderWindow.getSize().x){
		cloud5.setPosition(-rand()%500,rand()%500);
	}

	if(cloud6.getPosition().x > renderWindow.getSize().x){
		cloud6.setPosition(-rand()%500,rand()%500);
	}


	sf::Texture cloudTexture1;
	cloudTexture1.loadFromFile("Assets/Gameplay/Cloud1.png");
	cloud1.setTexture(cloudTexture1);
	if(rand()%2 <= 1){
		cloud1.setPosition(sf::Vector2f(cloud1.getGlobalBounds().left+1, cloud1.getPosition().y));
	}
	renderWindow.draw(cloud1);

	sf::Texture cloudTexture2;
	cloudTexture2.loadFromFile("Assets/Gameplay/Cloud2.png");
	cloud2.setTexture(cloudTexture2);
	cloud2.setPosition(sf::Vector2f(cloud2.getGlobalBounds().left+1, cloud2.getPosition().y));
	renderWindow.draw(cloud2);

	sf::Texture cloudTexture3;
	cloudTexture3.loadFromFile("Assets/Gameplay/Cloud3.png");
	cloud3.setTexture(cloudTexture3);
	cloud3.setPosition(sf::Vector2f(cloud3.getGlobalBounds().left+1, cloud3.getPosition().y));
	renderWindow.draw(cloud3);

	sf::Texture cloudTexture4;
	cloudTexture4.loadFromFile("Assets/Gameplay/Cloud3.png");
	cloud4.setTexture(cloudTexture4);
	cloud4.setPosition(sf::Vector2f(cloud4.getGlobalBounds().left+1, cloud4.getPosition().y));
	renderWindow.draw(cloud4);

	sf::Texture cloudTexture5;
	cloudTexture5.loadFromFile("Assets/Gameplay/Cloud2.png");
	cloud5.setTexture(cloudTexture5);
	cloud5.setPosition(sf::Vector2f(cloud5.getGlobalBounds().left+1, cloud5.getPosition().y));
	renderWindow.draw(cloud5);

	sf::Texture cloudTexture6;
	cloudTexture6.loadFromFile("Assets/Gameplay/Cloud1.png");
	cloud6.setTexture(cloudTexture6);
	cloud6.setPosition(sf::Vector2f(cloud6.getGlobalBounds().left+1, cloud6.getPosition().y));
	renderWindow.draw(cloud6);


	sf::Texture background1Texture;
	background1Texture.loadFromFile("Assets/Gameplay/BackgroundHills.png");
	sf::Sprite background1(background1Texture);

	background1.setPosition(0, renderWindow.getSize().y - background1.getLocalBounds().height);

	renderWindow.draw(background1);


	//Draw game stuff
	sf::Texture kingTexture;
	kingTexture.loadFromFile("Assets/Gameplay/King.png");

	King.setTexture(kingTexture);
	King.setPosition(0, renderWindow.getSize().y - King.getLocalBounds().height);

	renderWindow.draw(King);
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
