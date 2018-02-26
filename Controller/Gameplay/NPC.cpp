/*
 * NPC.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: Derek
 */

#include "../Headers/Gameplay/NPC.hpp"

NPC::NPC(int id) {
	// TODO Auto-generated constructor stub

	this->id = id;
	this->position.x = 0;
	this->position.y = 0;
	this->rotate = 0;
	this->reverseRotate = true;
	this->moveText = 0;
	this->movingIn = true;

	this->dismissed = false;
	this->moveOn = false;

	this->doneTalking = false;

	this->loadData();

	std::string filePath = "Assets/Gameplay/NPC/";

	if(!NPCTexture.loadFromFile(filePath + std::to_string(this->id) + ".png")) NPCTexture.loadFromFile(filePath + "Sir Cluckington.png");

	//This is for the Dialog talking tracking, so that after you respond this will show a different dialog from the beginning no input dialog.
	this->noResponseDialog = 0;
	this->drawDialog = false;
	this->doneDrawingDialog = false;
	this->dialogTextShown = 0;

	this->dialogTextTimeLimiterDefault = 1;
	this->dialogTextTimeLimiter = this->dialogTextTimeLimiterDefault;
	this->dialogTextTimeLimiterTemp = 0;

	defaultFont.loadFromFile("Assets/Fonts/GameFont.ttf");

}


NPC::~NPC() {
	// TODO Auto-generated destructor stub
}

void NPC::loadData(){
	std::string name = "";

	this->name = name;
}

void NPC::update(sf::RenderTarget &renderWindow){


	nameText.setCharacterSize(32);
	nameText.setFont(defaultFont);
	nameText.setString(this->name);

	nameText.setPosition(renderWindow.getSize().x - 300,30);

	dialogText.setFont(defaultFont);
	dialogText.setCharacterSize(20);
	dialogText.setPosition(renderWindow.getSize().x - 300,60);

	std::cout << "UPDATE" << std::endl;
	if(rotate > 5 || rotate < -5){
		reverseRotate = !reverseRotate;
	}
	std::cout << rotate << std::endl;

	if(reverseRotate) rotate +=1;
	else rotate -=1;


	if(position.x < NPCTexture.getSize().x && movingIn){
		position.x = position.x + (1);



	}else{
		if(movingIn){
			showDialog();
			movingIn = false;
		}
	}

	if(dismissed == true  && doneTalking){
		if(position.x < 0){
			moveOn = true;

		}else{
			moveOn = false;
			position.x-=(1);
		}
	}
	//Set text
	if(drawDialog){
		if(dialogTextTimeLimiterTemp >= dialogTextTimeLimiter){
			if(dialogString.at(dialogTextShown) == '.' || dialogString.at(dialogTextShown) == '!' || dialogString.at(dialogTextShown) == '?'){
				dialogTextTimeLimiter = 24;
				std::cout << "TIME LIMITEr" << std::endl;
			}else{
				dialogTextTimeLimiter = dialogTextTimeLimiterDefault;
			}

			if(dialogTextTimeLimiterTemp >= dialogTextTimeLimiter){
				if(!doneTalking){
					talkBuffer.loadFromFile("Assets/Gameplay/Soundfiles/blip.ogg");
					talk.setBuffer(talkBuffer);
					float random = (float) (std::rand()%(3/2) + 1);
					talk.setPitch(random);
					talk.play();
				}

				std::cout << "DRAW" << std::endl;
				if(dialogTextShown >= dialogString.length()-1){
					doneDrawingDialog = true;
				}else{
					dialogTextShown++;

					dialogText.setString(dialogString.substr(0,dialogTextShown+2));
					if(dialogText.getGlobalBounds().left + dialogText.getGlobalBounds().width > renderWindow.getSize().x){
						if(moveText == 0){
							moveText = dialogTextShown-5;
						}
						std::string tempString = dialogString;
						for(int i = 0; i < dialogTextShown%moveText; i++){
							if(i!=0 && i <= dialogTextShown/moveText){
								tempString.insert(i*moveText,"\n");
							}
						}

						dialogText.setString(tempString.substr(0,dialogTextShown+2));
					}
				}

				dialogTextTimeLimiterTemp = 0;
			}else{
				dialogTextTimeLimiterTemp ++;
			}

		}else{

			dialogTextTimeLimiterTemp ++;
		}

	}

	//IF IT IS DONE DRAWING DIALOG
	if(doneDrawingDialog){
		doneTalking = true;
	}
}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const{

	sf::Sprite NPCSprite;
	NPCSprite.setTexture(NPCTexture);

	if(movingIn || (dismissed && doneTalking)) NPCSprite.setPosition(target.getSize().x - position.x, (target.getSize().y - NPCSprite.getLocalBounds().height) + rotate);
	else NPCSprite.setPosition(target.getSize().x - position.x, (target.getSize().y - NPCSprite.getLocalBounds().height));
	target.draw(NPCSprite);

	//DRAW DIALOG
	if(drawDialog){


		target.draw(nameText);
		target.draw(dialogText);
	}



}

void NPC::showDialog(){
	this->drawDialog = true;
	this->doneDrawingDialog = false;
	dialogString = returnDialog();
}

std::string NPC::returnDialog(){
	std::string text = "We require additonal power pylons, may we build them?";

	return text;
}

std::string NPC::returnDialog(int response){
	std::string text = "";
	//0 response means yes,
	//1 response means no
	doneDrawingDialog = false;
	doneTalking = false;
	this->drawDialog = true;
	dialogTextShown = 0;

	if(response == 1){
		text = "Not enough minerals I see...";
	}else{
		text = "... Cool";
	}

	return text;

}

void NPC::dismiss(int response){
	this->dismissed = true;
	dialogString = returnDialog(response);
}

