/*
 * NPC.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: Derek
 */

#include "../Headers/Gameplay/NPC.hpp"

NPC::NPC(std::string name) {
	// TODO Auto-generated constructor stub

	this->name = name;
	this->position.x = 0;
	this->position.y = 0;
	this->rotate = 0;

	this->reverseRotate = true;

	this->movingIn = true;

	this->dismissed = false;
	this->moveOn = false;

	this->doneTalking = false;

	this->gatherData();

	std::string filePath = "Assets/Gameplay/NPC/";

	if(!NPCTexture.loadFromFile(filePath + name + ".png")) NPCTexture.loadFromFile(filePath + "Sir Cluckington.png");

	//This is for the Dialog talking tracking, so that after you respond this will show a different dialog from the beginning no input dialog.
	this->noResponseDialog = 0;
	this->drawDialog = false;
	this->doneDrawingDialog = false;
	this->dialogTextShown = 0;

	//defaultFont.loadFromFile("Assets/Fonts/font.ttf");

	nameText.setCharacterSize(32);
	nameText.setFont(defaultFont);
	nameText.setString(name);
}


NPC::~NPC() {
	// TODO Auto-generated destructor stub
}

void NPC::gatherData(){

}

void NPC::update(){
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
		showDialog();
		movingIn = false;
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
		std::cout << "DRAW" << std::endl;
		if(dialogTextShown >= dialogString.length()-1){
			doneDrawingDialog = true;
		}else{
			dialogTextShown++;

			dialogText.setString(dialogString.substr(0,dialogTextShown));
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
	NPCSprite.setPosition(target.getSize().x - position.x, (target.getSize().y - NPCSprite.getLocalBounds().height) + rotate);

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
	std::string text = "My name is jimmy";

	return text;
}

std::string NPC::returnDialog(int response){
	std::string text = "My name is jimmy";
	//0 response means yes,
	//1 response means no
	doneDrawingDialog = false;
	doneTalking = false;

	return text;

}

void NPC::dismiss(int response){
	this->dismissed = true;
	dialogString = returnDialog(response);
}

