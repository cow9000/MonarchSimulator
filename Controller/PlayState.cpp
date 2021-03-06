//
//  PlayState.cpp
//  EvoSim
//
//  Created by a on 1/26/18.
//  Copyright © 2018 a. All rights reserved.
//

#include "Headers/PlayState.hpp"

PlayState::PlayState(StateManager* stateManager){

	manager = new NPCManager(&GameSaveData);

	cloud1.setPosition(rand()%1500,rand()%1500);
	cloud2.setPosition(rand()%1500,rand()%1500);
	cloud3.setPosition(rand()%1500,rand()%1500);

	cloud4.setPosition(rand()%1500,rand()%1500);
	cloud5.setPosition(rand()%1500,rand()%1500);
	cloud6.setPosition(rand()%1500,rand()%1500);

	this->stateManager = stateManager;
	this->changeWindowSize = false;

	std::ifstream file2(GameManager::saveFileName);
	file2 >> GameSaveData;

	this->population = std::stoi(GameSaveData["population"].asString());
	this->happiness = std::stoi(GameSaveData["happiness"].asString());
	this->gold = std::stoi(GameSaveData["gold"].asString());
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

	this->showYesOrNo = false;
	this->chosenYes = false;
	this->chosenNo = false;
	this->haveSentChosenSignal = false;
	this->rotateYesOrNo = 0;
	this->backwards = false;

	this->isDusk = false;
	this->isNight = false;

	this->dayEnd = false;

	happinessNegative.loadFromFile("Assets/Gameplay/HappinessSmallNegative.png");
	happinessPositive.loadFromFile("Assets/Gameplay/HappinessSmall.png");
	goldNegative.loadFromFile("Assets/Gameplay/GoldSmallNegative.png");
	goldPositive.loadFromFile("Assets/Gameplay/GoldSmall.png");
	populationNegative.loadFromFile("Assets/Gameplay/PopulationSmallNegative.png");
	populationPositive.loadFromFile("Assets/Gameplay/PopulationSmall.png");
}


PlayState::~PlayState(){
	delete manager;
}

Json::Value& PlayState::returnGameSaveData(){
	return GameSaveData;
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

//startComplexity
void PlayState::updateState(sf::RenderTarget &renderWindow){

	popText.setString(std::to_string(population));
	happinessText.setString(std::to_string(happiness));
	goldText.setString(std::to_string(gold));

	popText.setPosition(70, renderWindow.getSize().y-150);
	happinessText.setPosition(70, renderWindow.getSize().y-100);
	goldText.setPosition(70, renderWindow.getSize().y-50);




	if(!dayEnd){
		manager->updateManager(renderWindow);

		if(manager->returnNpcNumber() == 2) {isDusk = true; isNight = false;}
		else if(manager->returnNpcNumber() > 3) {isNight = true; isDusk = false; }


		if(manager->returnNpcNumber() == 5){
			endOfDay();
		}else{
			if(manager->returnCurrentNPC()->isDoneTalking() && !manager->returnCurrentNPC()->isMovingIn()){
				int randomNumber = std::rand() %3 + 1;
				if(chosenYes){
					if(!haveSentChosenSignal){
						movingBlocks.clear();
						soundBuffer1.loadFromFile("Assets/Gameplay/Soundfiles/yes" + std::to_string(randomNumber) + ".ogg");
						sound1.setBuffer(soundBuffer1);
						sound1.play();
						this->haveSentChosenSignal = true;
						manager->returnCurrentNPC()->dismiss(0);

						// Add/Remove values

						this->happiness += manager->returnCurrentNPC()->returnHappiness();
						this->gold += manager->returnCurrentNPC()->returnGold();
						this->population += manager->returnCurrentNPC()->returnPopulation();
						//Add blocks
						movingBlocks.clear();
						for(int i = 0; i < abs(manager->returnCurrentNPC()->returnHappiness()/3) + abs(manager->returnCurrentNPC()->returnGold()/3) + abs(manager->returnCurrentNPC()->returnPopulation()/3); i++){
							if(i < abs(manager->returnCurrentNPC()->returnHappiness()/3)){
								if(manager->returnCurrentNPC()->returnHappiness() > 0){
									movingBlocks.push_back(new Block(true, 0, sf::Vector2f(0,rand()%3 + 1)));
								}else{
									movingBlocks.push_back(new Block(false, 0, sf::Vector2f(0,rand()%3 + 1)));
								}
							}else if(i < abs(manager->returnCurrentNPC()->returnGold()/3)){
								if(manager->returnCurrentNPC()->returnGold() > 0){
									movingBlocks.push_back(new Block(true, 1, sf::Vector2f(0,rand()%3 + 1)));
								}else{
									movingBlocks.push_back(new Block(false, 1, sf::Vector2f(0,rand()%3 + 1)));
								}
							}else{
								if(manager->returnCurrentNPC()->returnPopulation() > 0){
									movingBlocks.push_back(new Block(true, 2, sf::Vector2f(0,rand()%3 + 1)));
								}else{
									movingBlocks.push_back(new Block(false, 2, sf::Vector2f(0,rand()%3 + 1)));
								}
							}
						}

					}
				}else if(chosenNo){
					if(!haveSentChosenSignal){
						soundBuffer1.loadFromFile("Assets/Gameplay/Soundfiles/no" + std::to_string(randomNumber) + ".ogg");
						sound1.setBuffer(soundBuffer1);
						sound1.play();


						this->haveSentChosenSignal = true;

						manager->returnCurrentNPC()->dismiss(1);

						// Add/Remove values

						this->happiness += manager->returnCurrentNPC()->returnHappiness();
						this->gold += manager->returnCurrentNPC()->returnGold();
						this->population += manager->returnCurrentNPC()->returnPopulation();

						movingBlocks.clear();
						for(int i = 0; i < abs(manager->returnCurrentNPC()->returnHappiness()/3) + abs(manager->returnCurrentNPC()->returnGold()/3) + abs(manager->returnCurrentNPC()->returnPopulation()/3); i++){
							if(i < abs(manager->returnCurrentNPC()->returnHappiness()/3)){
								if(manager->returnCurrentNPC()->returnHappiness() > 0){
									movingBlocks.push_back(new Block(true, 0, sf::Vector2f(0,rand()%3 + 1)));
								}else{
									movingBlocks.push_back(new Block(false, 0, sf::Vector2f(0,rand()%3 + 1)));
								}
							}else if(i < abs(manager->returnCurrentNPC()->returnGold()/3)){
								if(manager->returnCurrentNPC()->returnGold() > 0){
									movingBlocks.push_back(new Block(true, 1, sf::Vector2f(0,rand()%3 + 1)));
								}else{
									movingBlocks.push_back(new Block(false, 1, sf::Vector2f(0,rand()%3 + 1)));
								}
							}else{
								if(manager->returnCurrentNPC()->returnPopulation() > 0){
									movingBlocks.push_back(new Block(true, 2, sf::Vector2f(0,rand()%3 + 1)));
								}else{
									movingBlocks.push_back(new Block(false, 2, sf::Vector2f(0,rand()%3 + 1)));
								}
							}
						}

					}
				}else if(showYesOrNo == false && chosenYes==false && chosenNo == false)showYesOrNo = true;



			}else{
				if(!manager->returnCurrentNPC()->isDismissed()){
					//This resets the NPC dialog thing
					this->haveSentChosenSignal = false;
					this->showYesOrNo = false;
					this->chosenYes = false;
					this->chosenNo = false;
				}
			}
		}


	}

}
//endComplexity

void PlayState::renderState(sf::RenderTarget &renderWindow){

	//Draw background stuff
	drawBackground(renderWindow);

	//Draw NPCs
	drawNPC(renderWindow);


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


    //Render GUI
	drawGUI(renderWindow);




}

void PlayState::drawNPC(sf::RenderTarget &renderWindow){
	if(!dayEnd){

		renderWindow.draw(*manager->returnCurrentNPC());
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


	if(manager->returnCurrentNPC()->getDrawDialog()){
		renderWindow.draw(manager->returnCurrentNPC()->returnNameText());
		renderWindow.draw(manager->returnCurrentNPC()->returnDialogText());
	}

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

				yesOrNo.setPosition(King.getLocalBounds().width-80, King.getPosition().y+150);

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

	renderWindow.draw(goldSprite);
	renderWindow.draw(populationSprite);
	renderWindow.draw(happinessSprite);
	renderWindow.draw(popText);
	renderWindow.draw(happinessText);
	renderWindow.draw(goldText);
	//Draw blocks
	for(int i = 0; i < movingBlocks.size(); i++){
		Block *block = movingBlocks.at(i);
		sf::Vector2f position = block->getAddedPosition();
		if(!(position.y < -50)){
			block->update();
			sf::Texture* texture;
			//Happiness, Gold, POpulation
			if(block->getType() == 0 && block->getPositive()) texture = &happinessPositive;
			else if(block->getType() == 0 && !block->getPositive()) texture = &happinessNegative;
			else if(block->getType() == 1 && block->getPositive()) texture = &goldPositive;
			else if(block->getType() == 1 && !block->getPositive()) texture = &goldNegative;
			else if(block->getType() == 2 && block->getPositive()) texture = &populationPositive;
			else if(block->getType() == 2 && !block->getPositive()) texture = &populationNegative;
			sf::Sprite blockSprite;
			blockSprite.setTexture(*texture);

			position.y = position.y + renderWindow.getSize().y-GuiSprite.getLocalBounds().height-10;
			blockSprite.setPosition(position);
			blockSprite.setScale(3.0,3.0);
			 renderWindow.draw(blockSprite);
		}
	}


}


void PlayState::startOfDay(){
	dayEnd = false;
	manager->newDay();
}

void PlayState::endOfDay(){

	dayEnd = true;
	showYesOrNo = false;
	chosenYes = false;
	chosenNo = false;
	isDusk = false;
	isNight = false;

	//POPULATION ADD
	this->minHappiness = 80 + (population/5);

	int happinessAdd = happiness - minHappiness;
	if(happinessAdd > 50) happinessAdd = 50;
	else if(happinessAdd < -50) happinessAdd = -50;

	population += happinessAdd;
	///////////////////////////

	startOfDay();

	GameSaveData["gold"] = std::to_string(gold);
	GameSaveData["population"] = std::to_string(population);
	GameSaveData["happiness"] = std::to_string(happiness);

	Json::StyledWriter writer;
	std::ofstream outFile;

	outFile.open(GameManager::saveFileName);
	outFile << writer.write(GameSaveData);
	outFile.close();

}
