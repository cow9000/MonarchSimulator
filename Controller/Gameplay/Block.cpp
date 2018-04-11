/*
 * Block.cpp
 *
 *  Created on: Mar 9, 2018
 *      Author: Derek
 */

#include "../Headers/Gameplay/Block.hpp"

Block::Block(bool positive, int type, sf::Vector2f movement){
	this->addedPosition.x = rand()%100;
	this->addedPosition.y = -20;
	this->positive = positive;
	this->type = type;
	this->movement = movement;
	life = 0;
}



void Block::update(){
	life++;
	addedPosition.x -= movement.x;
	addedPosition.y -= rand()%3;
}


