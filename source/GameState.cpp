#include "precompiled.h"
#include "GameState.h"
#include "constants.h"
#include "Rat.h"
#include "Utils.h"


GameState::GameState(sf::RenderWindow& window,
                     const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                     std::stack<State*>* const pStates
                     )
    : State(window, pSupportedKeys, pStates),
      playerInventory(5)
{
    stateType = STATE_UPDATES_AND_PROCESSES_EVENTS;

    initKeybinds("Config//gamestate_keybinds.ini");
    initView();
    initRenderTexture();
    initTilemap();
    initTextures();
    initPlayerInventory();
    initPlayer();
    initPlayerGui();
    initPauseMenu();
    initShader();
    initSystems();
}


GameState::~GameState()
{
    delete pTilemap;
    delete pPlayer;
    delete pPauseMenu;
    delete pPlayerGui;
    delete pEnemySystem;
    delete pTextTagSystem;

    for (auto enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
    {
        delete *enemy;
    }
}


void GameState::processEvent(const sf::Event& event)
{
    updateMousePosition(&view);
    
    // Setting the player's attack status
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        pPlayer->canAttack())
    {
        pPlayer->setAttackStatus(true);
    }
    else if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        pPlayer->setAttackStatus(false);
    }


    if (stateIsPaused)
    {
        processPauseMenuButtonsEvent(event);
    }
    else
    {
        if (event.type == sf::Event::KeyPressed && 
            event.key.code == keybinds.at("TOGGLE_PLAYER_INFO_TAB"))
        {
            pPlayerGui->toggleInfoTab();
        }
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
        pTextTagSystem->update(deltaTime);

        updateView();
        updatePlayerGui();
        updateEnemiesAndCombat(deltaTime);
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
    if (sf::Keyboard::isKeyPressed(keybinds.at(std::string("MOVE_UP"))))
    {
        pPlayer->move(0.f, -1.f, deltaTime);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at(std::string("MOVE_DOWN"))))
    {
        pPlayer->move(0.f, 1.f, deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(keybinds.at(std::string("MOVE_LEFT"))))
    {
        pPlayer->move(-1.f, 0.f, deltaTime);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at(std::string("MOVE_RIGHT"))))
    {
        pPlayer->move(1.f, 0.f, deltaTime);
    }
}


void GameState::updateTilemap(const float deltaTime)
{
    // FIXME: we are not updating the map with enemies instead of pPlayer
    pTilemap->update(*pPlayer, deltaTime, *pEnemySystem);
}


void GameState::updatePlayerGui()
{
    pPlayerGui->update();
}


void GameState::updateEnemiesAndCombat(const float deltaTime)
{
    auto enemy = enemies.begin();
    while (enemy != enemies.end())
    {
        (*enemy)->update(deltaTime, mousePosView);

        updateCombat(**enemy); 

        if ((*enemy)->isDead())
        {
            // Gaining the player's exp
            int exp = (int)((*enemy)->getExpForKilling());
            pPlayer->gainExp(exp);

            // Adding new pop-up text
            pTextTagSystem->addTextTag(
                EXPERIENCE_TAG, 
                sf::Vector2f(pPlayer->getCenter().x - GRID_SIZE, pPlayer->getPosition().y), 
                exp, "+ ", " exp"
            );

            delete *enemy;
            enemy = enemies.erase(enemy);
        }
        else
        {
            ++enemy;
        }
    }

    // Setting the player's attack status to false
    pPlayer->setAttackStatus(false);
}


void GameState::updateCombat(Enemy& enemy)
{
    // Attack of the player
    if (pPlayer->isAttacking() && 
        enemy.getGlobalBounds().contains(mousePosView) &&
        utils::getDistance(enemy.getCenter(), pPlayer->getCenter()) <= pPlayer->getAttackRange() &&
        enemy.canBeDamaged())
    {      
        // Damaging the enemy
        int damage = pPlayer->getDamage();
        enemy.loseHp(damage);

        enemy.restartDamageTimer();

        // Adding new pop-up text
        pTextTagSystem->addTextTag(DAMAGE_TAG, enemy.getPosition(), damage); 
    }


    // Attack of the enemy
    if (pPlayer->getGlobalBounds().intersects(enemy.getGlobalBounds()) &&
        pPlayer->canBeDamaged())
    {
        int damage = enemy.getDamage();
        pPlayer->loseHp(damage);

        pPlayer->restartDamageTimer();

        pTextTagSystem->addTextTag(DAMAGE_TAG, pPlayer->getPosition(), damage);
    }
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
    renderEnemies(renderTexture);
    pTextTagSystem->render(renderTexture);
    pTilemap->renderDeferred(renderTexture, &coreShader, pPlayer->getCenter());

    renderTexture.setView(renderTexture.getDefaultView());

    pPlayerGui->render(renderTexture);


    if (stateIsPaused)
    {
        pPauseMenu->render(renderTexture);
    }


    renderTexture.display();

    renderSprite.setTexture(renderTexture.getTexture());
    pTarget->draw(renderSprite);
}


void GameState::renderEnemies(sf::RenderTarget& target)
{
    for (auto enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
    {
        (*enemy)->render(target, &coreShader, pPlayer->getCenter(), true);
    }
}


void GameState::initTextures()
{
    textures["PLAYER_SHEET"].loadFromFile("Resources\\Images\\Entities\\Player\\player_sheet.png");
    textures["ENEMY_RAT_SHEET"].loadFromFile("Resources\\Images\\Entities\\Enemies\\rat_60x64.png");
    textures["WEAPON_SWORD"].loadFromFile("Resources\\Images\\Items\\Weapon\\sword.png");
}


void GameState::initView()
{
    view.setSize(sf::Vector2f((float)window.getSize().x / 1.5f, (float)window.getSize().y / 1.5f));
}


void GameState::initRenderTexture()
{
    renderTexture.create(window.getSize().x, window.getSize().y);
}


void GameState::initTilemap()
{
    pTilemap = new Tilemap("Resources\\Data\\tile_map.txt");
}


void GameState::initPlayerInventory()
{
    Sword s(textures["WEAPON_SWORD"], 2, 5);

    playerInventory.addItem(&s);
}


void GameState::initPlayer()
{
    pPlayer = new Player(
        GRID_SIZE * 2, 
        GRID_SIZE * 2, 
        textures["PLAYER_SHEET"], 
        playerInventory, 
        static_cast<Weapon&>(playerInventory[0])
    );
}


void GameState::initPlayerGui()
{
    pPlayerGui = new PlayerGui(*pPlayer, window);
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


void GameState::initSystems()
{
    pEnemySystem = new EnemySystem(enemies, textures, *pPlayer);
    pTextTagSystem = new TextTagSystem(font);
}
