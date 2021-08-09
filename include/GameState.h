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
#include "Inventory.h"


class GameState: public State
{
public:

                         GameState(sf::RenderWindow& window, 
                                   const std::unordered_map<std::string, sf::Keyboard::Key>& supportedKeys,
                                   std::stack<State*>& states
                                   );
    virtual              ~GameState();
                         
    virtual void         processEvent(const sf::Event& event);
    void                 processPauseMenuEvent(const sf::Event& event);
                         
    virtual void         update(const float deltaTime);
    void                 updateView();
    void                 updatePlayerKeyboardInput(const float deltaTime);
    void                 updateTilemap(const float deltaTime);
    void                 updateGui();
    void                 updateEnemiesAndCombat(const float deltaTime);
    void                 updateCombat(Enemy& enemy);
                         
    virtual void         render(sf::RenderTarget* pTarget = nullptr);
    void                 renderEnemies(sf::RenderTarget& target);
                         
private:                 
                         
    std::list<Enemy*>    enemies;
    EnemySystem*         pEnemySystem;
    TextTagSystem*       pTextTagSystem;
                         
    sf::View             view;
    Tilemap*             pTilemap;
                         
    Player*              pPlayer;
    PlayerGui*           pPlayerGui;
    Inventory            playerInventory;
                         
    PauseMenu*           pPauseMenu;
    sf::Font             font;
    sf::Shader           coreShader;

                         
    void                 initView();
    void                 initTilemap();
    virtual void         initTextures();
    void                 initPlayerInventory();
    void                 initPlayer();
    void                 initFont();
    void                 initGui();
    void                 initShader();
    void                 initSystems();

};


#endif // GAMESTATE_H
