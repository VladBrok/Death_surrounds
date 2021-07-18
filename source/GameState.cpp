#include "GameState.h"


GameState::GameState(sf::RenderWindow& window,
                     const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                     std::stack<State*>* const pStates
                     )
    : State(window, pSupportedKeys, pStates), pauseMenu(window)
{
    initKeybinds("Config//gamestate_keybinds.ini");
    initTextures();
    initPlayer();
}


GameState::~GameState()
{
    delete pPlayer;
}


void GameState::update(const float deltaTime)
{
    if (!stateIsPaused)
    {
        updateKeyboardInput(deltaTime);

        updateMousePosition();

        pPlayer->update(deltaTime);
    }
    else
    {
        // FIXME: Update pause menu
    }
}


void GameState::updateKeyboardInput(const float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_UP")))
    {
        pPlayer->move(0.f, -1.f, deltaTime);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_DOWN")))
    {
        pPlayer->move(0.f, 1.f, deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_LEFT")))
    {
        pPlayer->move(-1.f, 0.f, deltaTime);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_RIGHT")))
    {
        pPlayer->move(1.f, 0.f, deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(keybinds.at("CLOSE_STATE")))
    {
        //endActivity();

        pauseState();
    }
}


void GameState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = &window;
    }
    pPlayer->render(*pTarget);

    if (stateIsPaused)
    {
        pauseMenu.render(*pTarget);
    }
}


void GameState::initTextures()
{
    textures["PLAYER_SHEET"].loadFromFile("Images\\Sprites\\Player\\player_sheet.png");
}


void GameState::initPlayer()
{
    pPlayer = new Player(0.f, 0.f, textures["PLAYER_SHEET"]);
}
