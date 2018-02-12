#include "Headers/StateManager.hpp"
#include "Headers/SplashState.hpp"
#include "Headers/MainMenuState.hpp"
#include "Headers/OptionsMenuState.hpp"
#include "Headers/PlayState.hpp"
#include "Headers/PauseState.hpp"

StateManager::StateManager(){
	this->splashState = new SplashState(this);
    this->mainMenuState = new MainMenuState(this);
    this->optionsMenuState = new OptionsMenuState(this);
    this->playState = new PlayState(this);
    this->pauseState = new PauseState(this);
    
    this->currentState = splashState;
}

StateManager::~StateManager(){
	delete splashState;
    delete mainMenuState;
    delete optionsMenuState;
    delete playState;
    delete pauseState;
}

State& StateManager::returnSplashState(){
	return *splashState;
}

State& StateManager::returnMainMenuState(){
    return *mainMenuState;
}


State& StateManager::returnOptionsMenuState(){
    return *optionsMenuState;
}


State& StateManager::returnPlayState(){
    return *playState;
}


State& StateManager::returnPauseState(){
    return *pauseState;
}

State& StateManager::returnCurrentState(){
    return *currentState;
}

void StateManager::setCurrentState(States::implementedStates changeToState){
    if(changeToState == States::implementedStates::MAINMENU){
        currentState = mainMenuState;
    }else if(changeToState == States::implementedStates::OPTIONS){
        currentState = optionsMenuState;
    }else if(changeToState == States::implementedStates::PLAY){
        currentState = playState;
    }else if(changeToState == States::implementedStates::PAUSE){
        currentState = pauseState;
    }
}
