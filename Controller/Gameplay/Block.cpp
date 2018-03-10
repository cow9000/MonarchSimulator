/*
 * Block.cpp
 *
 *  Created on: Mar 9, 2018
 *      Author: Derek
 */

#include "../Headers/Gameplay/Block.hpp"

Block::Block(bool positive, int type, sf::Vector2f movement){
	this->positive = positive;
	this->type = type;
	this->movement = movement;
}



void Block::update(){
	addedPosition.x += movement.x;
	addedPosition.y += movement.y;
}


