#include "precompiled.h"
#include "GameState.h"


GameState::GameState(sf::RenderWindow& window,
                     const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                     std::stack<State*>* const pStates
                     )
    : State(window, pSupportedKeys, pStates), map(5, 5, 1)
{
    stateIsEventHandler = true;

    initKeybinds("Config//gamestate_keybinds.ini");
    initTextures();
    initPlayer();
    initPauseMenu();
}


GameState::~GameState()
{
    delete pPlayer;
    delete pPauseMenu;
}


void GameState::processEvents(const sf::Event& event)
{
    if (stateIsPaused)
    {
        processPauseMenuButtonEvents(event);
    }

    if (event.type == sf::Event::KeyPressed &&
        event.key.code == keybinds.at("CLOSE_STATE"))
    {
        if (!stateIsPaused)
        {
            pauseState();
        }
        else
        {
            unpauseState();
        }
    }
}


void GameState::processPauseMenuButtonEvents(const sf::Event& event)
{
    pPauseMenu->processMouseEvent(event, mousePosView);

    if (pPauseMenu->isButtonPressed("QUIT"))
    {
        endActivity();
    }
}


void GameState::update(const float deltaTime)
{
    updateMousePosition();

    if (!stateIsPaused)
    {
        updatePlayerKeyboardInput(deltaTime);
        pPlayer->update(deltaTime);
    }
}


void GameState::updatePlayerKeyboardInput(const float deltaTime)
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
}


void GameState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = &window;
    }

    map.render(*pTarget);
    pPlayer->render(*pTarget);

    if (stateIsPaused)
    {
        pPauseMenu->render(*pTarget);
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


void GameState::initPauseMenu()
{
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
    pPauseMenu = new PauseMenu(window, font);

    pPauseMenu->addButton("QUIT", "Go to main menu", 5);
}

