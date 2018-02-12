//
//  Chunk.cpp
//  EvoSim
//
//  Created by Vawdrey, Derek on 2/7/18.
//  Copyright © 2018 Vawdrey, Derek. All rights reserved.
//

#include "../Headers/Gameplay/Chunk.hpp"

Chunk::Chunk(sf::Vector2f chunkPosition){
    this->chunkPosition = chunkPosition;
    fillChunk();
}

Chunk::~Chunk(){
    for(int i = 0; i < tiles.size(); i++){
        delete tiles[i];
    }
}


void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::VertexArray vArray(sf::Points);
    for(int i = 0; i < tiles.size(); i++) {
    	sf::Vertex point;
    	point.position = sf::Vector2f(tiles[i]->returnPosition().x+(chunkPosition.x*GameManager::chunkSize.x),
    			tiles[i]->returnPosition().y+(chunkPosition.y*GameManager::chunkSize.y)
    	);
    	point.color = tiles[i]->returnCurrentColorValues();
        vArray.append(point);
    }
    
    target.draw(vArray);
}

void Chunk::updateChunk(){
    for(int i = 0; i < tiles.size(); i++){
        tiles[i]->updateTile(false, 0, 50);
    }
}

void Chunk::fillChunk(){
    for(int r = 0; r < GameManager::chunkSize.x; r++){
        for(int c = 0; c < GameManager::chunkSize.y; c++){
        	GameManager::TileType tile = GameManager::TileType::DIRT;
            tiles.push_back(new Tile(sf::Vector2f(r,c),tile));
        }
    }
}
