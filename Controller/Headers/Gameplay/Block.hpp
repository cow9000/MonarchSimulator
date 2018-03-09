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
	Block(bool positive, int direction);

	bool getPositive(){return positive;}
private:
	bool positive;
	sf::Vector2f addedPosition;
};


#endif /* CONTROLLER_GAMEPLAY_BLOCK_HPP_ */
