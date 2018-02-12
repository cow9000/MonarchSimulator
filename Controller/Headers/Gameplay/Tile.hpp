//
//  Tile.hpp
//  EvoSim
//
//  Created by Vawdrey, Derek on 1/26/18.
//  Copyright © 2018 Vawdrey, Derek. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include <SFML/Graphics.hpp>
#include "GameManager.hpp"

class Tile{
public:

	Tile();
    Tile(sf::Vector2f position);
    Tile(sf::Vector2f position, GameManager::TileType tileType);

	~Tile();

	GameManager::TileType returnTileType() { return tileType; }
	GameManager::BiomeType returnBiomeType() { return biomeType; }

    sf::Color returnMaxColorValues() { return maxColorValues; }
    sf::Color returnMinColorValues() { return minColorValues; }
    sf::Color returnCurrentColorValues() { return currentColorValues;}
    
    //Drawing return variables
    sf::Vector2f returnSize(){ return size; }
    sf::Vector2f returnPosition(){ return position; }
    
    bool returnCanLive(){ return canLive; }
    bool returnLiving(){ return living; }
    bool returnNeedsPartner() { return needsPartner;  }
    bool returnFlammable() { return flammable; }
    bool returnIsOnFire(){ return isOnFire; }
    
    double returnGrowthRare(){ return growthRate; }
    double returnReproductionRate(){ return reproductionRate; }
    double returnWaterConsumption(){ return waterConsumption; }
    double returnCurrentWaterLevels() { return currentWaterLevels; }
    double returnMaxWaterLevels(){ return maxWaterLevels; }
    double returnMinWaterLevels(){ return minWaterLevels; }
    double returnErosionResistance(){ return erosionResistance; }
    double returnDensity(){ return density; }
    double returnMass(){ return density * (size.x * size.y);}
    
    void updateTile(bool isRaining, double waterDistance, int temperature);
private:
    
    //Methods needed for tile creation
    void init(GameManager::TileType tileType, GameManager::BiomeType biomeType);
    void assignColors();
    void assignSize();
    void assignTileProperties();
    
    void die();
    
    
    GameManager::TileType tileType;
    GameManager::BiomeType biomeType;
    
    //Colors will represent how "alive the ground is, if indeed that tile is alive"
    sf::Color maxColorValues;
    sf::Color minColorValues;
    sf::Color currentColorValues;
    
    sf::Vector2f position;
    sf::Vector2f size;

    //Is this a rock, or a living plant things
    bool canLive;
    //If it is living, we assume it will grow.
    bool living;
    //Does it need a partner for reproduction
    bool needsPartner;
    bool flammable;
    bool isOnFire;
    
    //Living rates and data needed
    double growthRate;
    double reproductionRate;
    double waterConsumption;
    
    
    double currentWaterLevels;
    double maxWaterLevels;
    double minWaterLevels;


    //Natural consequences
    double erosionResistance;
    double density;

    
    
};

#endif /* Tile_hpp */
