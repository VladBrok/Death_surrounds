#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Player.h"
#include "PauseMenu.h"
#include "Tilemap.h"
#include "PlayerGui.h"
#include "Enemy.h"
#include "EnemySystem.h"
#include "TextTagSystem.h"
#include "LootSystem.h"
#include "Projectile.h"


class GameState: public State
{
public:

                              GameState(sf::RenderWindow& window, 
                                        const StringToKeyMap& supportedKeys,
                                        std::stack<State*>& states
                                        );
    virtual                   ~GameState();
                              
    virtual void              processEvent(const sf::Event& event);                         
    virtual void              update(const float deltaTime);                         
    virtual void              render(sf::RenderTarget* pTarget = nullptr);

                              
private:                      
                              
    std::list<Enemy*>         enemies;
    EnemySystem*              pEnemySystem;
    TextTagSystem*            pTextTagSystem;
    LootSystem*               pLootSystem;

    std::list<Projectile*>    projectiles;
                         
    sf::View                  view;
    Tilemap*                  pTilemap;
                              
    Player*                   pPlayer;
    PlayerGui*                pPlayerGui; 
    PauseMenu*                pPauseMenu;
    sf::Shader                coreShader;
                              
    sf::RectangleShape        gameOverScreen;
    sf::Text                  gameOverText;
    sf::Text                  gameOverInfoText;
    bool                      gameOver; 

    const bool                SHOW_HITBOXES;
    const bool                SHOW_COLLIDABLE_TILES;
    const bool                SHOW_ENEMY_SPAWNERS;
                              

    void                      processPauseMenuEvent(const sf::Event& event);
    void                      processGameOverEvent(const sf::Event& event); 

    void                      updateView();
    void                      updatePlayerKeyboardInput(const float deltaTime);
    void                      updateTilemap(const float deltaTime);
    void                      updateGui();
    void                      updateEnemiesAndCombat(const float deltaTime);
    void                      updateCombat(Enemy& enemy, const float deltaTime);
    void                      updateProjectiles(const float deltaTime);
    void                      updateIntersectionWithProjectiles(Enemy& enemy);

    void                      renderEnemies(sf::RenderTarget& target);
    void                      renderProjectiles(sf::RenderTarget& target);
    void                      renderGameOverScreen(sf::RenderTarget& target);

    void                      initView();
    void                      initTilemap();
    virtual void              initTextures();
    void                      initPlayer();
    void                      initGui();
    void                      initShader();
    void                      initSystems();
    void                      initGameOverScreen();
                              
    void                      deleteEnemies();

};


#endif // GAMESTATE_H
