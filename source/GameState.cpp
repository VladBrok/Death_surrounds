#include "precompiled.h"
#include "GameState.h"
#include "constants.h"
#include "Rat.h"
#include "Utils.h"
#include "Resources.h"
#include "Staff.h"
#include "Sword.h"


GameState::GameState(sf::RenderWindow& window,
                     const StringToKeyMap& supportedKeys,
                     std::stack<std::unique_ptr<State>>& states
                     )
    : State(window, supportedKeys, states),
      gameOver(false),
      SHOW_HITBOXES(false),
      SHOW_COLLIDABLE_TILES(false),
      SHOW_ENEMY_SPAWNERS(false)
{
    initKeybinds(resources::getGameStateKeybindsFile());
    initView();
    initTilemap();
    initTextures();
    initPlayer();
    initGui();
    initShader();
    initSystems();
    initGameOverScreen();
}


void GameState::processEvent(const sf::Event& event)
{
    updateMousePosition(&view);
    
    // Setting the player's attack status
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        player->canAttack())
    {
        player->setAttackStatus(true);
        player->restartAttackTimer();

        // Adding a new projectile
        if (player->getActiveWeaponType() == RANGED_WEAPON)
        {
            RangedWeapon* pRangedWeapon = dynamic_cast<RangedWeapon*>(player->getActiveItem());
            if (pRangedWeapon)
            {
                projectiles.push_back(
                    pRangedWeapon->allocateNewProjectile(
                        utils::getNormalizedDirection(player->getCenter(), mousePosView), 
                        player->getCenter()
                    )
                );
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased &&
             event.mouseButton.button == sf::Mouse::Left)
    {
        player->setAttackStatus(false);
    }


    if (stateIsPaused)
    {
        processPauseMenuEvent(event);
    }
    if (gameOver)
    {
        processGameOverEvent(event);
    }
    else if (!gameOver && !stateIsPaused && event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == keybinds.at("TOGGLE_PLAYER_INFO_TAB"))
        {
            playerGui->toggleInfoTab();
        }
        else if (event.key.code == keybinds.at("DROP_ITEM") && player->getActiveItem())
        {
            lootSystem->addLoot(player->getCenter().x + GRID_SIZE, 
                                player->getCenter().y, player->getActiveItem()
                                );
            player->removeActiveItem();
        }
        else if (event.key.code == keybinds.at("TOGGLE_INVENTORY_PANEL")) 
        {
            player->toggleInventoryPanel();
        }
    }

    
    // Pausing / unpausing the state
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == keybinds.at("PAUSE"))
    {
        stateIsPaused ? unpauseState(): pauseState();
    }
}


void GameState::update(const float deltaTime)
{
    if (!stateIsPaused)
    {
        if (!gameOver)
        {
            updatePlayerKeyboardInput(deltaTime);
            updateTilemap(deltaTime);
        }

        player->update(deltaTime, mousePosView, mousePosWindow, *textTagSystem); 

        if (!gameOver)
        {
            textTagSystem->update(deltaTime);
            lootSystem->update(*player);

            updateView();
            updateEnemiesAndCombat(deltaTime);
            updateGui();
        }
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

    tilemap->render(target, view, player->getGridPositionCenter(), &coreShader, player->getCenter(), SHOW_COLLIDABLE_TILES, SHOW_ENEMY_SPAWNERS);
    lootSystem->render(target);
    renderEnemies(target);
    player->render(target, &coreShader, player->getCenter(), SHOW_HITBOXES);

    if (!gameOver)
    {
        textTagSystem->render(target);
        renderProjectiles(target);
    }
    tilemap->renderDeferred(target, &coreShader, player->getCenter());

    target.setView(target.getDefaultView());

    playerGui->render(target);


    if (gameOver && player->deathAnimationIsDone())
    {
        renderGameOverScreen(target);
    }
    if (stateIsPaused)
    {
        pauseMenu->render(target);
    }
}


void GameState::processPauseMenuEvent(const sf::Event& event)
{
    pauseMenu->processEvent(event, mousePosWindow);

    if (pauseMenu->isButtonPressed("CONTINUE"))
    {
        unpauseState();
    }
    else if (pauseMenu->isButtonPressed("GO_TO_MAIN_MENU"))
    {
        endActivity();
    }
}


void GameState::processGameOverEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == keybinds.at("RESTART_GAME"))
    {
        gameOver = false;
        enemies.clear();

        initPlayer();
        initGui();
        initSystems();
    }
}


void GameState::updateView()
{
    view.setCenter(player->getCenter());

    // Don't letting the view to go outside the tilemap bounds
    if (tilemap->getMapSize().x >= view.getSize().x)
    {
        if (view.getCenter().x - view.getSize().x / 2.f < 0.f)
        {
            view.setCenter(view.getSize().x / 2.f, view.getCenter().y);
        }
        else if (view.getCenter().x + view.getSize().x / 2.f > tilemap->getMapSize().x)
        {
            view.setCenter(tilemap->getMapSize().x - view.getSize().x / 2.f, view.getCenter().y);
        }
    }
    if (tilemap->getMapSize().y >= view.getSize().y)
    {
        if (view.getCenter().y - view.getSize().y / 2.f < 0.f)
        {
            view.setCenter(view.getCenter().x, view.getSize().y / 2.f);
        }
        else if (view.getCenter().y + view.getSize().y / 2.f > tilemap->getMapSize().y)
        {
            view.setCenter(view.getCenter().x, tilemap->getMapSize().y - view.getSize().y / 2.f);
        }
    }


    view.setCenter(
        sf::Vector2f(
            std::floor(view.getCenter().x), 
            std::floor(view.getCenter().y)
        )
    );
}


void GameState::updatePlayerKeyboardInput(const float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(keybinds.at(std::string("MOVE_UP"))))
    {
        player->move(0.f, -1.f, deltaTime);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at(std::string("MOVE_DOWN"))))
    {
        player->move(0.f, 1.f, deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(keybinds.at(std::string("MOVE_LEFT"))))
    {
        player->move(-1.f, 0.f, deltaTime);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at(std::string("MOVE_RIGHT"))))
    {
        player->move(1.f, 0.f, deltaTime);
    }
}


void GameState::updateTilemap(const float deltaTime)
{
    tilemap->update(*player, deltaTime, *enemySystem);
}


void GameState::updateGui()
{
    playerGui->update(*player);
}


void GameState::updateEnemiesAndCombat(const float deltaTime)
{
    updateProjectiles(deltaTime);

    auto enemy = enemies.begin();
    while (enemy != enemies.end())
    {
        (*enemy)->update(deltaTime);

        updateCombat(**enemy, deltaTime); 

        if ((*enemy)->isDead())
        {
            // Checking for the level up and gaining the player's exp
            int exp = (int)((*enemy)->getExpForKilling());
            if (player->getExp() + exp >= player->getExpForNextLevel())
            {
                textTagSystem->addTextTag(
                    LEVEL_UP_TAG,
                    sf::Vector2f(player->getCenter().x - GRID_SIZE, player->getPosition().y),
                    "Level up!"
                );
            }
            player->gainExp(exp);

            // Adding the new pop-up exp text
            textTagSystem->addTextTag(
                EXPERIENCE_TAG, 
                sf::Vector2f(), 
                exp, "+ ", " exp"
            );
            textTagSystem->setBackElementPosition(
                player->getCenter().x - textTagSystem->getBackElementSize().x / 2.f, 
                player->getPosition().y
            );

            // Adding the loot
            lootSystem->addLoot(
                (*enemy)->getPosition().x, 
                (*enemy)->getPosition().y, 
                (*enemy)->getDroppingItem()
            );
        }
        if ((*enemy)->isDead() || (*enemy)->canBeDespawned(view))
        {
            enemy = enemies.erase(enemy);
        }
        else
        {
            ++enemy;
        }

        // Checking if player is dead
        if (player->isDead())
        {
            gameOver = true;
            return;
        }
    }

    player->setAttackStatus(false);
}


void GameState::updateCombat(Enemy& enemy, const float)
{
    // Melee attack of the player
    if (player->isAttacking() && 
        player->getActiveWeaponType() == MELEE_WEAPON && 
        enemy.getGlobalBounds().contains(mousePosView) &&
        utils::getDistance(enemy.getCenter(), player->getCenter()) <= player->getAttackRange() &&
        enemy.canBeDamaged())
    {      
        int damage = player->getDamage();
        enemy.loseHp(damage);

        enemy.restartDamageTimer();

        // Adding new pop-up text
        textTagSystem->addTextTag(DAMAGE_TAG, enemy.getPosition(), damage);       
    }


    // Attack of the enemy
    if (player->getGlobalBounds().intersects(enemy.getGlobalBounds()) &&
        player->canBeDamaged() &&
        enemy.canAttack())
    {
        int damage = enemy.getDamage();
        player->loseHp(damage);

        player->restartDamageTimer();
        enemy.restartAttackTimer();

        textTagSystem->addTextTag(DAMAGE_TAG, player->getPosition(), damage);
    }

    updateIntersectionWithProjectiles(enemy);
}


void GameState::updateProjectiles(const float deltaTime)
{
    auto projectile = projectiles.begin();
    while (projectile != projectiles.end())
    {
        (*projectile)->update(deltaTime);
        if ((*projectile)->canBeRemoved())
        {
            projectile = projectiles.erase(projectile);
        }
        else
        {
            ++projectile;
        }
    }
}


void GameState::updateIntersectionWithProjectiles(Enemy& enemy)
{
    auto projectile = projectiles.begin();
    while (projectile != projectiles.end())
    {
        if ((*projectile)->checkIntersection(enemy) && enemy.canBeDamaged())
        {
            int damage = player->getDamage();
            enemy.restartDamageTimer();
            enemy.loseHp(damage);
            textTagSystem->addTextTag(DAMAGE_TAG, enemy.getPosition(), damage);

            projectile = projectiles.erase(projectile);
        }
        else
        {
            ++projectile;
        }
    }
}


void GameState::renderEnemies(sf::RenderTarget& target)
{
    for (auto enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
    {
        (*enemy)->render(target, &coreShader, player->getCenter(), SHOW_HITBOXES);
    }
}


void GameState::renderProjectiles(sf::RenderTarget& target)
{
    for (auto projectile = projectiles.begin(); projectile != projectiles.end(); ++ projectile)
    {
        (*projectile)->render(target);
    }
}


void GameState::renderGameOverScreen(sf::RenderTarget& target)
{
    target.draw(gameOverScreen);
    target.draw(gameOverText);
    target.draw(gameOverInfoText);
}


void GameState::initTextures()
{
    textures["PLAYER_SHEET"].loadFromFile(resources::getPlayerTextureFile());
    textures["ENEMY_RAT_SHEET"].loadFromFile(resources::getRatTextureFile());
    textures["ENEMY_SPIDER_SHEET"].loadFromFile(resources::getSpiderTextureFile());
    textures["ENEMY_SKELETON_SHEET"].loadFromFile(resources::getSkeletonTextureFile());
    textures["ENEMY_REAPER_SHEET"].loadFromFile(resources::getReaperTextureFile());
    textures["WEAPON_SWORD"].loadFromFile(resources::getSwordTextureFile());
    textures["WEAPON_STAFF"].loadFromFile(resources::getStaffTextureFile());
    textures["WEAPON_UNLOADED_STAFF"].loadFromFile(resources::getUnloadedStaffTextureFile());
    textures["STAFF_ORB"].loadFromFile(resources::getStaffOrbTextureFile());
    textures["HP_BAR"].loadFromFile(resources::getPlayerHpBarTextureFile());
    textures["EXP_BAR"].loadFromFile(resources::getPlayerExpBarTextureFile());
    textures["FOOD"].loadFromFile(resources::getFoodTextureFile());
    textures["INVENTORY_PANEL"].loadFromFile(resources::getInventoryPanelTextureFile());
}


void GameState::initView()
{
    view.setSize(sf::Vector2f((float)window.getSize().x / 1.5f, (float)window.getSize().y / 1.5f));
}


void GameState::initTilemap()
{
    tilemap.reset(new Tilemap(resources::getTilemapFile()));
}


void GameState::initPlayer()
{
    player.reset(new Player(
        GRID_SIZE * 2, 
        GRID_SIZE * 2, 
        textures["PLAYER_SHEET"],
        textures["INVENTORY_PANEL"],
        window
    ));


    Sword sword(textures["WEAPON_SWORD"], 2, 5);
    player->addItemToInventory(&sword, true);

    Staff staff(textures["WEAPON_STAFF"], textures["WEAPON_UNLOADED_STAFF"], textures["STAFF_ORB"], 1, 1);
    player->addItemToInventory(&staff);
}


void GameState::initGui()
{
    /*=============== Player GUI ===============*/

    playerGui.reset(new PlayerGui(*player, font, window, textures["HP_BAR"], textures["EXP_BAR"]));


    /*=============== Pause menu ===============*/

    pauseMenu.reset(new PauseMenu(window, font));
    pauseMenu->addButton("CONTINUE", "Continue", 2);
    pauseMenu->addButton("GO_TO_MAIN_MENU", "Go to main menu", 5);
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
    enemySystem.reset(new EnemySystem(enemies, textures, *player));
    textTagSystem.reset(new TextTagSystem(font));
    lootSystem.reset(new LootSystem(textures["FOOD"]));
}


void GameState::initGameOverScreen()
{
    gameOverScreen.setSize(static_cast<sf::Vector2f>(window.getSize()));
    gameOverScreen.setFillColor(sf::Color(160, 0, 0, 120));

    gameOverText.setFont(font);
    gameOverText.setCharacterSize((unsigned)utils::percentToPixels(4.f, (int)(window.getSize().x + window.getSize().y)));
    gameOverText.setString("YOU DIED");
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(
        gameOverScreen.getSize().x / 2.f - gameOverText.getGlobalBounds().width / 2.f,
        gameOverScreen.getSize().y / 2.f - gameOverText.getGlobalBounds().height * 1.5f
    );

    gameOverInfoText.setFont(font);
    gameOverInfoText.setCharacterSize((unsigned)utils::percentToPixels(2.5f, (int)(window.getSize().x + window.getSize().y)));
    gameOverInfoText.setString("Press Space key to respawn");
    gameOverInfoText.setPosition(
        gameOverScreen.getSize().x / 2.f - gameOverInfoText.getGlobalBounds().width / 2.f,
        gameOverText.getPosition().y + gameOverText.getGlobalBounds().height + utils::percentToPixels(5.f, (int)window.getSize().y)
    );
}
