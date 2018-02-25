/*
 * NPCManager.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: Derek
 */

#include "../Headers/Gameplay/NPCManager.hpp"

NPCManager::NPCManager() {
	// TODO Auto-generated constructor stub
	this->NpcNumber = 0;
	newDay();

}

void NPCManager::addRandomNPC(){
	NPCStack.push(NPC("Sir Cluckington"));
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

