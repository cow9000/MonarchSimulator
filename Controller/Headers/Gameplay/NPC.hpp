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
#include <SFML/Audio.hpp>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include "../../../Json/json/json.h"


class NPC : public sf::Drawable{
public:
	NPC(int id, Json::Value* GameSaveData);
	virtual ~NPC();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::RenderTarget &renderWindow);

	std::string returnDialog();
	std::string returnDialog(int response);

	void dismiss(int response);

	bool isDoneTalking(){ return doneTalking; }
	bool isDismissed(){ return dismissed; }
	bool isMovingIn(){ return movingIn; }
	bool getDrawDialog() {return drawDialog; }
	bool canMoveOn() {return moveOn;}

	int returnHappiness();
	int returnPopulation();
	int returnGold();

	sf::Text returnNameText(){ return nameText; }
	sf::Text returnDialogText(){ return dialogText; }
private:
	sf::Clock movementClock;
	void loadData();
	void saveData();
	void showDialog();

	std::string name;
	int id;

	sf::Texture NPCTexture;
	sf::Vector2f position;

	int noResponseDialog;


	bool reverseRotate;
	int rotate;

	bool movingIn;
	bool dismissed;
	bool doneTalking;
	bool moveOn;

	int response;


	int dialogTextShown;
	int dialogTextTimeLimiter;
	int dialogTextTimeLimiterDefault;
	int dialogTextTimeLimiterTemp;
	int moveText;
	bool drawDialog;
	bool doneDrawingDialog;
	sf::Font defaultFont;
	std::string dialogString;
	sf::Text nameText;
	sf::Text dialogText;


	sf::SoundBuffer talkBuffer;
	sf::Sound talk;

	Json::Value NPCData;
	Json::Value* GameSaveData;

};

#endif /* CONTROLLER_GAMEPLAY_NPC_HPP_ */
