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
    void                 processGameOverEvent(const sf::Event& event);
                         
    virtual void         update(const float deltaTime);
    void                 updateView();
    void                 updatePlayerKeyboardInput(const float deltaTime);
    void                 updateTilemap(const float deltaTime);
    void                 updateGui();
    void                 updateEnemiesAndCombat(const float deltaTime);
    void                 updateCombat(Enemy& enemy);
    void                 updateLootSystem();
                         
    virtual void         render(sf::RenderTarget* pTarget = nullptr);
    void                 renderEnemies(sf::RenderTarget& target);
    void                 renderGameOverScreen(sf::RenderTarget& target);
                         
private:                 
                         
    std::list<Enemy*>    enemies;
    EnemySystem*         pEnemySystem;
    TextTagSystem*       pTextTagSystem;
    LootSystem*          pLootSystem;
                         
    sf::View             view;
    Tilemap*             pTilemap;
                         
    Player*              pPlayer;
    PlayerGui*           pPlayerGui;
                         
    PauseMenu*           pPauseMenu;
    sf::Font             font;
    sf::Shader           coreShader;
    
    sf::RectangleShape   gameOverScreen;
    sf::Text             gameOverText;
    sf::Text             gameOverInfoText;
    bool                 gameOver;                

                         
    void                 initView();
    void                 initTilemap();
    virtual void         initTextures();
    void                 initPlayer();
    void                 initFont();
    void                 initGui();
    void                 initShader();
    void                 initSystems();
    void                 initGameOverScreen();

    void                 deleteEnemies();

};


#endif // GAMESTATE_H
