//
//  Chunk.hpp
//  EvoSim
//
//  Created by Vawdrey, Derek on 2/7/18.
//  Copyright © 2018 Vawdrey, Derek. All rights reserved.
//

#ifndef Chunk_hpp
#define Chunk_hpp

#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include <vector>

class Chunk : public sf::Drawable{
    
public:
    Chunk(sf::Vector2f chunkPosition);
    ~Chunk();
    void updateChunk();
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    
    void fillChunk();
    
    sf::Vector2f chunkPosition;
    std::vector<Tile*> tiles;
    
};

#endif /* Chunk_hpp */
