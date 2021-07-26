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
    initRenderTexture();
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
        updateView();
        updatePlayerKeyboardInput(deltaTime);
        updateTilemap(deltaTime);
        pPlayer->update(deltaTime); 
    }
}


void GameState::updateView()
{
    view.setCenter(
        pPlayer->getPosition().x + pPlayer->getGlobalBounds().width / 2.f,
        pPlayer->getPosition().y + pPlayer->getGlobalBounds().height / 2.f
    );
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


void GameState::updateTilemap(const float deltaTime)
{
    pTilemap->updateCollision(*pPlayer, deltaTime);
}


void GameState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = &window;
    }

    renderTexture.clear();


    renderTexture.setView(view);

    pTilemap->render(renderTexture, pPlayer);
    pPlayer->render(renderTexture);

    renderTexture.setView(renderTexture.getDefaultView());

    if (stateIsPaused)
    {
        pPauseMenu->render(renderTexture);
    }


    renderTexture.display();

    renderSprite.setTexture(renderTexture.getTexture());
    pTarget->draw(renderSprite);


    // Rendering directly to the pTarget (window)

    //pTarget->setView(view);

    //pTilemap->render(*pTarget);
    //pPlayer->render(*pTarget);

    //pTarget->setView(renderTexture.getDefaultView());

    //if (stateIsPaused)
    //{
    //    pPauseMenu->render(*pTarget);
    //}
}


void GameState::initTextures()
{
    textures["PLAYER_SHEET"].loadFromFile("Resources\\Images\\Entities\\Player\\player_sheet.png");
}


void GameState::initView()
{
    view.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
}


void GameState::initRenderTexture()
{
    renderTexture.create(window.getSize().x, window.getSize().y);
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

