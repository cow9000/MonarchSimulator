//
//  PlayState.hpp
//  EvoSim
//
//  Created by Vawdrey, Derek on 1/26/18.
//  Copyright © 2018 Vawdrey, Derek. All rights reserved.
//

#ifndef PlayState_hpp
#define PlayState_hpp

#include "State.hpp"
#include "Gameplay/Chunk.hpp"

class PlayState : public State {
public:
	PlayState(StateManager* stateManager);
    ~PlayState();
    void processState(sf::Event &event, sf::RenderTarget &renderWindow);
    void updateState(sf::RenderTarget &renderWindow);
    void renderState(sf::RenderTarget &renderWindow);
private:
    bool changeWindowSize;
    bool fillChunks;
    std::vector<Chunk*> chunks;
};

#endif /* PlayState_hpp */
