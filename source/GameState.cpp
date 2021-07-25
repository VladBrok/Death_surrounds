#include "precompiled.h"
#include "GameState.h"
#include "constants.h"


GameState::GameState(sf::RenderWindow& window,
                     const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                     std::stack<State*>* const pStates
                     )
    : State(window, pSupportedKeys, pStates)
{
    stateType = STATE_UPDATES_AND_PROCESSES_EVENTS;

    initKeybinds("Config//gamestate_keybinds.ini");
    initView();
    initTilemap();
    initTextures();
    initPlayer();
    initPauseMenu();
}


GameState::~GameState()
{
    delete pTilemap;
    delete pPlayer;
    delete pPauseMenu;
}


void GameState::processEvent(const sf::Event& event)
{
    updateMousePosition(&view);

    if (stateIsPaused)
    {
        processPauseMenuButtonsEvent(event);
    }

    if (event.type == sf::Event::KeyPressed &&
        event.key.code == keybinds.at("PAUSE"))
    {
        stateIsPaused ? unpauseState(): pauseState();
    }
}


void GameState::processPauseMenuButtonsEvent(const sf::Event& event)
{
    pPauseMenu->processEvent(event, mousePosWindow);

    if (pPauseMenu->isButtonPressed("GO_TO_MAIN_MENU"))
    {
        endActivity();
    }
}


void GameState::update(const float deltaTime)
{
    if (!stateIsPaused)
    {
        updatePlayerKeyboardInput(deltaTime);
        pPlayer->update(deltaTime);
        updateView();
    }
}


void GameState::updateView()
{
    view.setCenter(pPlayer->getPosition());
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


    pTarget->setView(view);

    pTilemap->render(*pTarget);
    pPlayer->render(*pTarget);

    pTarget->setView(pTarget->getDefaultView());


    if (stateIsPaused)
    {
        pPauseMenu->render(*pTarget);
    }
}


void GameState::initTextures()
{
    textures["PLAYER_SHEET"].loadFromFile("Resources\\Images\\Entities\\Player\\player_sheet.png");
}


void GameState::initView()
{
    view.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
}


void GameState::initTilemap()
{
    pTilemap = new Tilemap(TILEMAP_SIZE_X, TILEMAP_SIZE_Y, TILEMAP_SIZE_Z);
    pTilemap->loadFromFile("Resources\\Data\\tile_map.txt");
}


void GameState::initPlayer()
{
    pPlayer = new Player(0.f, 0.f, textures["PLAYER_SHEET"]);
}


void GameState::initPauseMenu()
{
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
    pPauseMenu = new PauseMenu(window, font);

    pPauseMenu->addButton("GO_TO_MAIN_MENU", "Go to main menu", 5);
}

