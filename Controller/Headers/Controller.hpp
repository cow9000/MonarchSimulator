//
//  Controller.hpp
//  EvoSim
//
//  Created by a on 1/24/18.
//  Copyright © 2018 a. All rights reserved.
//

#ifndef Controller_hpp
#define Controller_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "StateManager.hpp"

class Controller{
    public:
        Controller( );
        sf::RenderWindow& returnWindow();
    private:
    
        void start();
    
        //Process Events
        void processWindow();
        //Update
        void updateWindow(sf::Time timePerFrame);
        //Draw
        void drawWindow();
    
        sf::RenderWindow window;
        StateManager stateManager;
        sf::Sound gameMusic;
        sf::SoundBuffer buffer;
};

#endif /* Controller_hpp */
