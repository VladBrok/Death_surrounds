#include "precompiled.h"
#include "GameState.h"
#include "constants.h"
#include "Rat.h"


GameState::GameState(sf::RenderWindow& window,
                     const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                     std::stack<State*>* const pStates
                     )
    : State(window, pSupportedKeys, pStates),
      pEnemySystem(nullptr)
{
    stateType = STATE_UPDATES_AND_PROCESSES_EVENTS;

    initKeybinds("Config//gamestate_keybinds.ini");
    initView();
    initRenderTexture();
    initTilemap();
    initTextures();
    initPlayer();
    initPlayerGUI();
    initPauseMenu();
    initShader();
    initEnemySystem();
}


GameState::~GameState()
{
    delete pTilemap;
    delete pPlayer;
    delete pPauseMenu;
    delete pPlayerGUI;
    delete pEnemySystem;

    for (size_t i = 0; i < enemies.size(); ++i)
    {
        delete enemies[i];
    }
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
        updateTilemap(deltaTime);

        pPlayer->update(deltaTime, mousePosView); 

        updateView();
        updatePlayerGUI();
        updateEnemySystem(deltaTime);
    }
}


void GameState::updateView()
{
    view.setCenter(pPlayer->getCenter());

    // Don't letting the view to go outside the tilemap bounds
    if (pTilemap->getMapSize().x >= view.getSize().x)
    {
        if (view.getCenter().x - view.getSize().x / 2.f < 0.f)
        {
            view.setCenter(view.getSize().x / 2.f, view.getCenter().y);
        }
        else if (view.getCenter().x + view.getSize().x / 2.f > pTilemap->getMapSize().x)
        {
            view.setCenter(pTilemap->getMapSize().x - view.getSize().x / 2.f, view.getCenter().y);
        }
    }
    if (pTilemap->getMapSize().y >= view.getSize().y)
    {
        if (view.getCenter().y - view.getSize().y / 2.f < 0.f)
        {
            view.setCenter(view.getCenter().x, view.getSize().y / 2.f);
        }
        else if (view.getCenter().y + view.getSize().y / 2.f > pTilemap->getMapSize().y)
        {
            view.setCenter(view.getCenter().x, pTilemap->getMapSize().y - view.getSize().y / 2.f);
        }
    }
}


void GameState::updatePlayerKeyboardInput(const float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_UP")))
    {
        pPlayer->move(0.f, -1.f, deltaTime);
        pPlayer->gainExp(40);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_DOWN")))
    {
        pPlayer->move(0.f, 1.f, deltaTime);
        pPlayer->loseExp(40);
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
    pTilemap->update(*pPlayer, deltaTime, *pEnemySystem);
}


void GameState::updatePlayerGUI()
{
    pPlayerGUI->update();
}


void GameState::updateEnemySystem(const float deltaTime)
{
    pEnemySystem->update(deltaTime, mousePosView);
}


void GameState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = &window;
    }

    renderTexture.clear();


    renderTexture.setView(view);

    pTilemap->render(renderTexture, pPlayer->getGridPositionCenter(), &coreShader, pPlayer->getCenter(), true, true);
    pPlayer->render(renderTexture, &coreShader, pPlayer->getCenter(), true);
    pEnemySystem->render(renderTexture, coreShader, pPlayer->getCenter(), true);
    pTilemap->renderDeferred(renderTexture, &coreShader, pPlayer->getCenter());

    renderTexture.setView(renderTexture.getDefaultView());

    pPlayerGUI->render(renderTexture);


    if (stateIsPaused)
    {
        pPauseMenu->render(renderTexture);
    }


    renderTexture.display();

    renderSprite.setTexture(renderTexture.getTexture());
    pTarget->draw(renderSprite);
}


void GameState::initTextures()
{
    textures["PLAYER_SHEET"].loadFromFile("Resources\\Images\\Entities\\Player\\player_sheet.png");
    textures["ENEMY_RAT_SHEET"].loadFromFile("Resources\\Images\\Entities\\Enemies\\rat_60x64.png");
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
    pTilemap = new Tilemap("Resources\\Data\\tile_map.txt");
}


void GameState::initPlayer()
{
    pPlayer = new Player(GRID_SIZE * 2, GRID_SIZE * 2, textures["PLAYER_SHEET"]);
}


void GameState::initPlayerGUI()
{
    pPlayerGUI = new PlayerGUI(*pPlayer, window);
}


void GameState::initPauseMenu()
{
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
    pPauseMenu = new PauseMenu(window, font);

    pPauseMenu->addButton("GO_TO_MAIN_MENU", "Go to main menu", 5);
}


void GameState::initShader()
{
    coreShader.loadFromFile(
        "Resources\\Shaders\\vertex_shader.vert", 
        "Resources\\Shaders\\fragment_shader.frag"
    );
}


void GameState::initEnemySystem()
{
    pEnemySystem = new EnemySystem(enemies, textures);
}
