

#ifndef State_hpp
#define State_hpp

#include <SFML/Graphics.hpp>

class StateManager;

class State{
public:
    virtual ~State() {};
    virtual void processState(sf::Event &event, sf::RenderTarget &renderWindow) = 0;
    virtual void updateState(sf::RenderTarget &renderWindow) = 0;
    virtual void renderState(sf::RenderTarget &renderWindow) = 0;
protected:
    StateManager* stateManager;
};

#endif //State_hpp 
