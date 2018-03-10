/*
 * Block.hpp
 *
 *  Created on: Mar 9, 2018
 *      Author: Derek
 */

#ifndef CONTROLLER_GAMEPLAY_BLOCK_HPP_
#define CONTROLLER_GAMEPLAY_BLOCK_HPP_

#include <SFML/Graphics.hpp>

class Block{
public:
	Block(bool positive, int type, sf::Vector2f movement);

	void update();

	bool getPositive(){return positive;}
	sf::Vector2f getAddedPosition(){return addedPosition;}
private:
	bool positive;
	int type;
	sf::Vector2f movement;
	sf::Vector2f addedPosition;
};


#endif /* CONTROLLER_GAMEPLAY_BLOCK_HPP_ */
