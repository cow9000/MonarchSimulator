//
//  Controller.cpp
//  EvoSim
//
//  Created by Vawdrey, Derek on 1/24/18.
//  Copyright © 2018 Vawdrey, Derek. All rights reserved.
//

#include "Headers/Controller.hpp"

Controller::Controller(){

	window.create(sf::VideoMode(640,480), "Kingdom Simulator");
	buffer.loadFromFile("Assets/music.ogg");
	gameMusic.setBuffer(buffer);

	gameMusic.play();
	gameMusic.setLoop(true);
	//gameMusic.openFromFile("Assets/music.ogg");
	//gameMusic.play();

	//Start the game
    start();
}

void Controller::start(){

    sf::Clock fpsClock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);
    
    while(window.isOpen()){
        processWindow();
        
        
        

        while(accumulator > ups){
            //Limit FPS here to 60 FPS
        	accumulator -= ups;
            updateWindow(accumulator);
            
        }
        drawWindow();
        accumulator += fpsClock.restart();
    }


}

void Controller::processWindow(){
    
    //Process the events of the main window and the game states.
    sf::Event event;
    while(window.pollEvent(event)){
        
        //Default for all game states, if the window is closed, close the window
        if(event.type == sf::Event::Closed){
                window.close();
        }else{
            stateManager.returnCurrentState().processState(event,window);
        }
        
    }
}

void Controller::updateWindow(sf::Time timePerFrame){
    //Put updating for game states in here
    stateManager.returnCurrentState().updateState(window);


}

void Controller::drawWindow(){
    window.clear();
    
    //Draw the current state
    stateManager.returnCurrentState().renderState(window);
    
    window.display();
}

sf::RenderWindow& Controller::returnWindow(){
    return window;
}
