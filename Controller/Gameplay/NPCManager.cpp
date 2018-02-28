/*
 * NPCManager.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: Derek
 */

#include "../Headers/Gameplay/NPCManager.hpp"
#include "../Headers/Gameplay/GameManager.hpp"
#include "../../Json/json/json.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

inline bool file_exists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

NPCManager::NPCManager(Json::Value* GameSaveData) {
	// TODO Auto-generated constructor stub
	this->GameSaveData = GameSaveData;
	this->NpcNumber = 0;
	generateConfigFile();
	newDay();

}

void NPCManager::generateConfigFile(){
	std::ofstream file_id;

	std::string fileName = GameManager::saveFileName;

	if(!file_exists(fileName)){
		file_id.open(fileName);


		Json::Value event;

		//0 false, 1 true

		event["gold"] = "200";
		event["population"] = "100";
		event["happiness"] = "100";

		for(int i = 0; i < 2000; i++){
			event[std::to_string(i)]["stillVisit"] = "1";
			event[std::to_string(i)]["timesVisited"] = "0";
			event[std::to_string(i)]["countVisit"] = "0";
			event[std::to_string(i)]["randomizedDialog"] = "0";
		}

		Json::StyledWriter styledWriter;
		file_id << styledWriter.write(event);
		file_id.close();

	}
}



void NPCManager::addRandomNPC(){
	NPCStack.push(NPC(std::rand()%3,GameSaveData));
}

NPCManager::~NPCManager() {
	// TODO Auto-generated destructor stub
}

int NPCManager::returnNpcNumber(){
	return NpcNumber;
}

NPC * NPCManager::returnCurrentNPC(){
	if(NPCStack.empty()) return nullptr;
	return &NPCStack.top();
}

void NPCManager::nextNPC(){

	NpcNumber ++;
	NPCStack.pop();

}

void NPCManager::newDay(){
	NpcNumber = 0;
	for(int i = 0; i < 5; i++){
		addRandomNPC();
	}
}

void NPCManager::updateManager(sf::RenderTarget &renderWindow){
	returnCurrentNPC()->update(renderWindow);

	if(!NPCStack.empty()){
		if(NPCStack.top().canMoveOn()){
			nextNPC();
		}
	}
};

