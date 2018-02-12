//
//  GameManager.hpp
//  EvoSim
//
//  Created by Vawdrey, Derek on 1/26/18.
//  Copyright © 2018 Vawdrey, Derek. All rights reserved.
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <SFML/Graphics.hpp>

namespace GameManager{
    //Tiles that are able to be created
    enum TileType{
    	//Living tile types
    	GRASS, TREE,

		//Not living tile types
		ROCK, WATER, SAND, MUD, DIRT

    };
    

    //http://kids.nceas.ucsb.edu/biomes/
    enum BiomeType{
    	//Aquatic Biomes
    	FRESHWATER, FRESHWATER_WETLANDS, MARINE, CORAL_REEF, ESTUARIES,

		//Terrestrial Biomes
    	TUNDRA, RAINFOREST, SAVANNA, TAIGA, TEMPERATE_FOREST, TEMPERATE_GRASSLAND, ALPINE, CHAPARRAL, DESERT
    };

    const double GRAVITY = 0.98;

    //Colors
    const sf::Color buttonSelectedColor(0,224,127);
    const sf::Color buttonUnSelectedColor(255,255,255);
    
    const sf::Vector2f chunkSize(16,16);
    
    

};



#endif /* GameManager_hpp */
