#include "precompiled.h"
#include "GameState.h"
#include "constants.h"
#include "Rat.h"
#include "Utils.h"
#include "Resources.h"


GameState::GameState(sf::RenderWindow& window,
                     const std::unordered_map<std::string, sf::Keyboard::Key>& supportedKeys,
                     std::stack<State*>& states
                     )
    : State(window, supportedKeys, states),
      playerInventory(5)
{
    stateType = STATE_UPDATES_AND_PROCESSES_EVENTS;

    initKeybinds(resources::getGameStateKeybindsFile());
    initView();
    initTilemap();
    initTextures();
    initPlayerInventory();
    initPlayer();
    initFont();
    initGui();
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
        processPauseMenuEvent(event);
    }
    else
    {
        if (event.type == sf::Event::KeyPressed && 
            event.key.code == keybinds.at("TOGGLE_PLAYER_INFO_TAB"))
        {
            pPlayerGui->toggleInfoTab();
        }
    }

    // Pausing / unpausing the state
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == keybinds.at("PAUSE"))
    {
        stateIsPaused ? unpauseState(): pauseState();
    }
}


void GameState::processPauseMenuEvent(const sf::Event& event)
{
    pPauseMenu->processEvent(event, mousePosWindow);

    if (pPauseMenu->isButtonPressed("CONTINUE"))
    {
        unpauseState();
    }
    else if (pPauseMenu->isButtonPressed("GO_TO_MAIN_MENU"))
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
        updateGui();
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


    view.setCenter(
        sf::Vector2f(
            (float)((int)view.getCenter().x), 
            (float)((int)view.getCenter().y)
        )
    );
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
    pTilemap->update(*pPlayer, deltaTime, *pEnemySystem);
}


void GameState::updateGui()
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
        }
        if ((*enemy)->isDead() || (*enemy)->canBeDespawned(view))
        {
            delete *enemy;
            enemy = enemies.erase(enemy);
        }
        else
        {
            ++enemy;
        }
    }

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


    sf::RenderTarget& target = *pTarget;
    target.setView(view);

    pTilemap->render(target, view, pPlayer->getGridPositionCenter(), &coreShader, pPlayer->getCenter(), false, false);
    pPlayer->render(target, &coreShader, pPlayer->getCenter(), true);
    renderEnemies(target);
    pTextTagSystem->render(target);
    pTilemap->renderDeferred(target, &coreShader, pPlayer->getCenter());

    target.setView(target.getDefaultView());

    pPlayerGui->render(target);


    if (stateIsPaused)
    {
        pPauseMenu->render(target);
    }
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
    textures["PLAYER_SHEET"].loadFromFile(resources::getPlayerTextureFile());
    textures["ENEMY_RAT_SHEET"].loadFromFile(resources::getRatTextureFile());
    textures["WEAPON_SWORD"].loadFromFile(resources::getSwordTextureFile());
    textures["HP_BAR"].loadFromFile(resources::getPlayerHpBarTextureFile());
    textures["EXP_BAR"].loadFromFile(resources::getPlayerExpBarTextureFile());
}


void GameState::initView()
{
    view.setSize(sf::Vector2f((float)window.getSize().x / 1.5f, (float)window.getSize().y / 1.5f));
}


void GameState::initTilemap()
{
    pTilemap = new Tilemap(resources::getTilemapFile());
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


void GameState::initFont()
{
    font.loadFromFile(resources::getFontFile());
}


void GameState::initGui()
{
    /*=============== Player GUI ===============*/

    pPlayerGui = new PlayerGui(*pPlayer, font, window, textures["HP_BAR"], textures["EXP_BAR"]);


    /*=============== Pause menu ===============*/

    pPauseMenu = new PauseMenu(window, font);
    pPauseMenu->addButton("CONTINUE", "Continue", 2);
    pPauseMenu->addButton("GO_TO_MAIN_MENU", "Go to main menu", 5);
}


void GameState::initShader()
{
    coreShader.loadFromFile(
        resources::getVertexShaderFile(), 
        resources::getFragmentShaderFile()
    );
}


void GameState::initSystems()
{
    pEnemySystem = new EnemySystem(enemies, textures, *pPlayer);
    pTextTagSystem = new TextTagSystem(font);
}
