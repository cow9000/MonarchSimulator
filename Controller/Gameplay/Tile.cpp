//
//  Tile.cpp
//  EvoSim
//
//  Created by Vawdrey, Derek on 1/26/18.
//  Copyright © 2018 Vawdrey, Derek. All rights reserved.
//

#include "../Headers/Gameplay/Tile.hpp"
#include <stdlib.h>
#include <time.h>

Tile::Tile(){
    init(GameManager::TileType::DIRT, GameManager::BiomeType::TEMPERATE_FOREST);
}

Tile::Tile(sf::Vector2f position){
    this->position = position;
    init(GameManager::TileType::DIRT, GameManager::BiomeType::TEMPERATE_FOREST);
}

Tile::Tile(sf::Vector2f position, GameManager::TileType tileType){
    this->position = position;
    init(tileType, GameManager::BiomeType::ALPINE);
}

Tile::~Tile(){
    
}


void Tile::init(GameManager::TileType tileType, GameManager::BiomeType biomeType){
    this->tileType = tileType;
    this->biomeType = biomeType;
    
    assignColors();
    assignSize();
    assignTileProperties();
    
}

void Tile::assignColors(){
    
    
    
    //Colors will represent how "alive the ground is, if indeed that tile is alive, or how rocky it is"
    maxColorValues = sf::Color(0,255,0);
    minColorValues = sf::Color(0,127,0);
    
    if(tileType == GameManager::TileType::SAND){
        maxColorValues = sf::Color(255,255,204);
        minColorValues = sf::Color(255,255,150);
    }else if(tileType == GameManager::TileType::DIRT || tileType == GameManager::TileType::MUD){
        maxColorValues = sf::Color(255, 150, 255);
        minColorValues = sf::Color(139, 68, 143);
    }else if(tileType == GameManager::TileType::ROCK){
        maxColorValues = sf::Color(222, 222, 222);
        minColorValues = sf::Color(119, 119, 119);
    }else if(tileType == GameManager::TileType::WATER){
    	maxColorValues = sf::Color(20, 125, 254);
    	minColorValues = sf::Color(10, 105, 119);
    }
    
    if(tileType != GameManager::TileType::ROCK){
    currentColorValues = sf::Color(rand() % maxColorValues.r + minColorValues.r,rand() % maxColorValues.g + minColorValues.g,rand() % maxColorValues.b + minColorValues.b);
    }else{
    	double value = rand()%maxColorValues.r + minColorValues.r;
    	currentColorValues = sf::Color(value,value,value);
    }
    
    
    
    
}

void Tile::assignSize(){
    
    size = sf::Vector2f(1,1);
    
}

void Tile::assignTileProperties(){
    
    if(tileType == GameManager::TileType::GRASS || tileType == GameManager::TileType::TREE){
        canLive = true;
    }else{
        canLive = false;
    }
    
    //If the tile can live, then it is living, if not
    if(canLive) living = true;
    else living = false;

    //If it is living it needs a partner (will implement Asexual reproduction later)
    if(living) needsPartner = true;
    else needsPartner = false;
    
    //If the object can live (is made of wood, grass, fur, etc, it is flammable.
    if(canLive) flammable = true;
    else flammable = false;
    
    isOnFire = false;
    
    //Living rates and data needed
    growthRate = 0.23;
    reproductionRate = 0.01;
    
    //If Tile is living it will consume water, if it isn't, it won't
    if(living) waterConsumption = 0.01;
    else waterConsumption = 0;
    
    //Natural consequences
    erosionResistance = 0.02;
    density = 0.68;
    
}

void Tile::die(){
    living = false;
}

void Tile::updateTile(bool isRaining, double waterDistance, int temperature){
    

    if(isRaining){
        currentWaterLevels ++;
    }
    //0 to 1, 0 being far away. 1 being right by
    currentWaterLevels += waterDistance;
    
    currentWaterLevels -= temperature/32;
    
    if(currentWaterLevels > maxWaterLevels) currentWaterLevels = maxWaterLevels;
    
    
    /////////////////////////////
    //Tile Dies.
    if(currentWaterLevels < minWaterLevels) die();
    
    //If tile is dead change color
    if(!living && canLive){
        double grayScale = (currentColorValues.r + currentColorValues.g + currentColorValues.b)/3;
        currentColorValues = sf::Color(grayScale,grayScale,grayScale);
    }else if(living && canLive){
        //TODO: MODIFY THIS SO IT FITS WITH PERCENTAGES BETWEEN CURRENTWATERLEVERS AND MAXWATERLEVELS/MINWATERLEVELS
        double R = 2;
        double G = 2;
        double B = 2;
        currentColorValues = sf::Color(R,G,B);
    }else{

    	double r = currentColorValues.r + 1;
    	if(r > maxColorValues.r) r = minColorValues.r;
    	double g = currentColorValues.g + 1;
    	if(g > maxColorValues.g) g = minColorValues.g;
    	double b = currentColorValues.b + 1;
    	if(b > maxColorValues.b) b = minColorValues.b;
    	sf::Color newColor = sf::Color(r,g,b);
    	currentColorValues = newColor;

    	if(rand()%10 < 5){
    		minColorValues.g -= 1;

    		minColorValues.b -= 1;
    		maxColorValues.g +=1;
    		maxColorValues.r +=1;
    		maxColorValues.b +=1;
    	}
    }
    //currentColorValues = sf::Color(rand() % maxColorValues.r + minColorValues.r,rand() % maxColorValues.g + minColorValues.g,rand() % maxColorValues.b + minColorValues.b);
    //////////////////////////////
}

