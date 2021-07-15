#include "GameState.h"


GameState::GameState(sf::RenderWindow* pWindow,
                     const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                     std::stack<State*>* const pStates
                     )
    : State(pWindow, pSupportedKeys, pStates)
{
    initKeybinds("Config//gamestate_keybinds.ini");
}


void GameState::update(const float deltaTime)
{
    updateKeyboardInput(deltaTime);

    updateMousePosition();
}


void GameState::updateKeyboardInput(const float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_UP")))
    {
        player.move(0.f, -1.f, deltaTime);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_DOWN")))
    {
        player.move(0.f, 1.f, deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_LEFT")))
    {
        player.move(-1.f, 0.f, deltaTime);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_RIGHT")))
    {
        player.move(1.f, 0.f, deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(keybinds.at("CLOSE_STATE")))
    {
        endActivity();
    }
}


void GameState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = pWindow;
    }
    player.render(pTarget);
}
