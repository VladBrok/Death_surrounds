#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Entity.h"


class GameState: public State
{
public:

    GameState(sf::RenderWindow* pWindow, 
              const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
              std::stack<State*>* const pStates
              );
    virtual void update(const float deltaTime);
    virtual void updateKeyboardInput(const float deltaTime);
    virtual void render(sf::RenderTarget* pTarget = nullptr);

private:

    Entity player;
};


#endif // GAMESTATE_H
