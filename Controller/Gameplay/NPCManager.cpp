/*
 * NPCManager.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: Derek
 */

#include "../Headers/Gameplay/NPCManager.hpp"
#include "../../Json/json/json.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

inline bool file_exists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

NPCManager::NPCManager() {
	// TODO Auto-generated constructor stub
	this->NpcNumber = 0;
	generateConfigFile();
	newDay();

}

void NPCManager::generateConfigFile(){
	std::ofstream file_id;
	std::string fileName = "SaveFile.json";
	file_id.open(fileName);

	if(!file_exists(fileName)){

		Json::Value event;

		//0 false, 1 true

		//NPCID, stillVisit
		event["0"]["StillVisit"] = "1";
		event["0"]["TimesVisited"] = "0";
		event["0"]["CountVisit"] = "0";
		event["0"]["RandomizedDialog"] = "0";

		Json::StyledWriter styledWriter;
		file_id << styledWriter.write(event);
		file_id.close();

	}
}



void NPCManager::addRandomNPC(){
	NPCStack.push(NPC(2));
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

