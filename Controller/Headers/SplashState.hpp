/*
 * SplashState.hpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Derek
 */

#ifndef CONTROLLER_HEADERS_SPLASHSTATE_HPP_
#define CONTROLLER_HEADERS_SPLASHSTATE_HPP_


#include "State.hpp"

class SplashState : public State {
public:
	SplashState(StateManager* stateManager);
    ~SplashState();
    void processState(sf::Event &event, sf::RenderTarget &renderWindow);
    void updateState(sf::RenderTarget &renderWindow);
    void renderState(sf::RenderTarget &renderWindow);
private:
    sf::Clock splashClock;
    double timePassed;
    bool wait;
    sf::Texture logoTexture;
};



#endif /* CONTROLLER_HEADERS_SPLASHSTATE_HPP_ */
