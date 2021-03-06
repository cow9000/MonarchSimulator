/*
 * NPCManager.hpp
 *
 *  Created on: Feb 23, 2018
 *      Author: Derek
 */

#ifndef CONTROLLER_GAMEPLAY_NPCMANAGER_HPP_
#define CONTROLLER_GAMEPLAY_NPCMANAGER_HPP_

#include <stack>
#include "NPC.hpp"

class NPCManager {
public:
	NPCManager(Json::Value* GameSaveData);
	virtual ~NPCManager();

	NPC *returnCurrentNPC();

	int returnNpcNumber();
	void updateManager(sf::RenderTarget &renderWindow);

	void newDay();

private:
	void addRandomNPC();
	void nextNPC();
	void generateConfigFile();

	int NpcNumber;
	std::stack<NPC> NPCStack;
	Json::Value* GameSaveData;
};

#endif /* CONTROLLER_GAMEPLAY_NPCMANAGER_HPP_ */
