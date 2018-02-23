/*
 * NPC.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: Derek
 */

#include "../Headers/Gameplay/NPC.hpp"
#include <iostream>

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
		this->doneTalking = true;
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
}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const{

	sf::Sprite NPCSprite;
	NPCSprite.setTexture(NPCTexture);
	NPCSprite.setPosition(target.getSize().x - position.x, (target.getSize().y - NPCSprite.getLocalBounds().height) + rotate);

	target.draw(NPCSprite);

}

std::string NPC::returnDialog(){
	std::string text = "";

	return text;
}

std::string NPC::returnDialog(int response){
	std::string text = "";
	//0 response means yes,
	//1 response means no


	return text;
}

void NPC::dismiss(int response){
	this->dismissed = true;
	this->doneTalking = true;
	returnDialog(response);
}

