/*
 * NPC.hpp
 *
 *  Created on: Feb 23, 2018
 *      Author: Derek
 */

#ifndef CONTROLLER_GAMEPLAY_NPC_HPP_
#define CONTROLLER_GAMEPLAY_NPC_HPP_

#include <String>
#include <iostream>
#include <SFML/Graphics.hpp>

class NPC : public sf::Drawable{
public:
	NPC(std::string name);
	virtual ~NPC();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update();

	std::string returnDialog();
	std::string returnDialog(int response);

	void dismiss(int response);

	bool isDoneTalking(){ return doneTalking; }
	bool isDismissed(){ return dismissed; }
	bool isMovingIn(){ return movingIn; }
	bool canMoveOn() {return moveOn;}
private:
	sf::Clock movementClock;
	void gatherData();
	void saveData();
	void showDialog();

	std::string name;

	sf::Texture NPCTexture;
	sf::Vector2f position;

	int noResponseDialog;


	bool reverseRotate;
	int rotate;

	bool movingIn;
	bool dismissed;
	bool doneTalking;
	bool moveOn;


	int dialogTextShown;
	bool drawDialog;
	bool doneDrawingDialog;
	sf::Font defaultFont;
	std::string dialogString;

	sf::Text dialogText;
};

#endif /* CONTROLLER_GAMEPLAY_NPC_HPP_ */
