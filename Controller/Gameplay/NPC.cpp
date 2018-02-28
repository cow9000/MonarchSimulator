/*
 * NPC.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: Derek
 */

#include "../Headers/Gameplay/NPC.hpp"
#include "../Headers/Gameplay/GameManager.hpp"

inline bool file_exists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}



NPC::NPC(int id) {
	// TODO Auto-generated constructor stub

	this->id = id;
	this->position.x = 0;
	this->position.y = 0;
	this->rotate = 0;
	this->response = 0;
	this->reverseRotate = true;
	this->moveText = 0;
	this->movingIn = true;

	this->dismissed = false;
	this->moveOn = false;

	this->doneTalking = false;

	this->loadData();

	std::string filePath = "Assets/Gameplay/NPC/";

	if(!NPCTexture.loadFromFile(filePath + std::to_string(this->id) + ".png")) NPCTexture.loadFromFile(filePath + "Sir Cluckington.png");

	//This is for the Dialog talking tracking, so that after you respond this will show a different dialog from the beginning no input dialog.
	this->noResponseDialog = 0;
	this->drawDialog = false;
	this->doneDrawingDialog = false;
	this->dialogTextShown = 0;

	this->dialogTextTimeLimiterDefault = 1;
	this->dialogTextTimeLimiter = this->dialogTextTimeLimiterDefault;
	this->dialogTextTimeLimiterTemp = 0;

	defaultFont.loadFromFile("Assets/Fonts/GameFont.ttf");

}


NPC::~NPC() {
	// TODO Auto-generated destructor stub
}

void NPC::loadData(){
	std::string name = "";
	std::string fileName = "data/npc" + std::to_string(id) + ".json";
	if(!file_exists(fileName)){

		std::ofstream file_id;
		file_id.open(fileName);

		Json::Value event;

		//0 false, 1 true

		//NPCID, stillVisit
		event[std::to_string(id)]["name"] = "NEED TO CHANGE - " + std::to_string(id);

		for(int i = 0; i < 10; i++){

		event[std::to_string(id)]["dialog"][std::to_string(i)]["text"] = "DESC_CHANGE[" + std::to_string(i) + "] - " + std::to_string(id);
		event[std::to_string(id)]["dialog"][std::to_string(i)]["NeedResponse"] = "1";

		event[std::to_string(id)]["yes"][std::to_string(i)]["text"] = "YES[" + std::to_string(i) + "] TO CHANGE - " + std::to_string(id);
		event[std::to_string(id)]["yes"][std::to_string(i)]["population"] = "100";
		event[std::to_string(id)]["yes"][std::to_string(i)]["happiness"] = "100";
		event[std::to_string(id)]["yes"][std::to_string(i)]["gold"] = "100";

		event[std::to_string(id)]["no"][std::to_string(i)]["text"] = "NO[" + std::to_string(i) + "] TO CHANGE - " + std::to_string(id);
		event[std::to_string(id)]["no"][std::to_string(i)]["population"] = "-100";
		event[std::to_string(id)]["no"][std::to_string(i)]["happiness"] = "-100";
		event[std::to_string(id)]["no"][std::to_string(i)]["gold"] = "-100";

		}



		Json::StyledWriter styledWriter;
		file_id << styledWriter.write(event);
		file_id.close();
	}

	std::ifstream file(fileName);
	file >> NPCData;
	name = NPCData[std::to_string(id)]["name"].asString();

	std::ifstream file2(GameManager::saveFileName);
	file2 >> GameSaveData;


	this->name = name;
}

void NPC::saveData(){
	std::cout << "COUNT VISIT - " << GameSaveData[std::to_string(id)]["countVisit"].asString() << std::endl;
	if(GameSaveData[std::to_string(id)]["countVisit"].asString() == "1"){
		if(std::stoi(GameSaveData[std::to_string(id)]["timesVisited"].asString()) < 9){
			GameSaveData[std::to_string(id)]["timesVisited"] = std::to_string(std::stoi(GameSaveData[std::to_string(id)]["timesVisited"].asString()) + 1);
			std::cout << GameSaveData[std::to_string(id)]["timesVisited"] << std::endl;
		}else{
			GameSaveData[std::to_string(id)]["timesVisited"] = "0";
		}
	}
}

void NPC::update(sf::RenderTarget &renderWindow){


	nameText.setCharacterSize(32);
	nameText.setFont(defaultFont);
	nameText.setString(this->name);

	nameText.setPosition(renderWindow.getSize().x - 300,30);

	dialogText.setFont(defaultFont);
	dialogText.setCharacterSize(20);
	dialogText.setPosition(renderWindow.getSize().x - 300,60);

	if(rotate > 5 || rotate < -5){
		reverseRotate = !reverseRotate;
	}

	if(reverseRotate) rotate +=1;
	else rotate -=1;


	if(position.x < NPCTexture.getSize().x && movingIn){
		position.x = position.x + (1);



	}else{
		if(movingIn){
			showDialog();
			movingIn = false;
		}
	}

	if(dismissed == true  && doneTalking){
		if(position.x < 0){
			moveOn = true;

		}else{
			moveOn = false;
			position.x-=(1);
		}
	}
	//Set text
	if(drawDialog){
		if(dialogTextTimeLimiterTemp >= dialogTextTimeLimiter){
			if(dialogString.at(dialogTextShown) == '.' || dialogString.at(dialogTextShown) == '!' || dialogString.at(dialogTextShown) == '?'){
				dialogTextTimeLimiter = 24;
			}else{
				dialogTextTimeLimiter = dialogTextTimeLimiterDefault;
			}

			if(dialogTextTimeLimiterTemp >= dialogTextTimeLimiter){
				if(!doneTalking){
					talkBuffer.loadFromFile("Assets/Gameplay/Soundfiles/blip.ogg");
					talk.setBuffer(talkBuffer);
					float random = (float) (std::rand()%(3/2) + 1);
					talk.setPitch(random);
					talk.play();
				}

				if(dialogTextShown >= dialogString.length()-1){
					doneDrawingDialog = true;
				}else{
					dialogTextShown++;

					dialogText.setString(dialogString.substr(0,dialogTextShown+2));
					if(dialogText.getGlobalBounds().left + dialogText.getGlobalBounds().width > renderWindow.getSize().x){
						if(moveText == 0){
							moveText = dialogTextShown-5;
						}
						std::string tempString = dialogString;
						for(int i = 0; i < dialogTextShown%moveText; i++){
							if(i!=0 && i <= dialogTextShown/moveText){
								tempString.insert(i*moveText,"\n");
							}
						}

						dialogText.setString(tempString.substr(0,dialogTextShown+2));
					}
				}

				dialogTextTimeLimiterTemp = 0;
			}else{
				dialogTextTimeLimiterTemp ++;
			}

		}else{

			dialogTextTimeLimiterTemp ++;
		}

	}

	//IF IT IS DONE DRAWING DIALOG
	if(doneDrawingDialog){
		doneTalking = true;
	}
}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const{

	sf::Sprite NPCSprite;
	NPCSprite.setTexture(NPCTexture);

	if(movingIn || (dismissed && doneTalking)) NPCSprite.setPosition(target.getSize().x - position.x, (target.getSize().y - NPCSprite.getLocalBounds().height) + rotate);
	else NPCSprite.setPosition(target.getSize().x - position.x, (target.getSize().y - NPCSprite.getLocalBounds().height));
	target.draw(NPCSprite);

	//DRAW DIALOG
	if(drawDialog){


		target.draw(nameText);
		target.draw(dialogText);
	}



}

void NPC::showDialog(){
	this->drawDialog = true;
	this->doneDrawingDialog = false;
	dialogString = returnDialog();
}

std::string NPC::returnDialog(){
	std::string timesVisited = GameSaveData[std::to_string(id)]["timesVisited"].asString();
	std::string text = NPCData[std::to_string(id)]["dialog"][timesVisited]["text"].asString();

	return text;
}

std::string NPC::returnDialog(int response){
	std::string text = "";
	//0 response means yes,
	//1 response means no
	doneDrawingDialog = false;
	doneTalking = false;
	this->drawDialog = true;
	dialogTextShown = 0;

	std::string timesVisited = GameSaveData[std::to_string(id)]["timesVisited"].asString();

	if(response == 1){
		text = NPCData[std::to_string(id)]["no"][timesVisited]["text"].asString();
	}else{
		text = NPCData[std::to_string(id)]["yes"][timesVisited]["text"].asString();
	}

	return text;

}

void NPC::dismiss(int response){
	this->dismissed = true;
	this->response = response;
	dialogString = returnDialog(response);
	saveData();
}

int NPC::returnHappiness(){
	int happiness = 0;
	std::string timesVisited = GameSaveData[std::to_string(id)]["timesVisited"].asString();
	std::string responseString = "yes";
	if(this->response == 1) responseString = "no";
	happiness = std::stoi(NPCData[std::to_string(id)][responseString][timesVisited]["happiness"].asString());
	return happiness;
}

int NPC::returnPopulation(){
	int population = 0;
	std::string timesVisited = GameSaveData[std::to_string(id)]["timesVisited"].asString();
	std::string responseString = "yes";
	if(this->response == 1) responseString = "no";
	population = std::stoi(NPCData[std::to_string(id)][responseString][timesVisited]["population"].asString());
	return population;
}

int NPC::returnGold(){
	int gold = 0;
	std::string timesVisited = GameSaveData[std::to_string(id)]["timesVisited"].asString();
	std::string responseString = "yes";
	if(this->response == 1) responseString = "no";
	gold = std::stoi(NPCData[std::to_string(id)][responseString][timesVisited]["gold"].asString());
	return gold;
}
