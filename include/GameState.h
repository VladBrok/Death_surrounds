#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Player.h"
#include "PauseMenu.h"
#include "Tilemap.h"
#include "PlayerGUI.h"
#include "Enemy.h"
#include "EnemySystem.h"
#include "TextTagSystem.h"
#include "Inventory.h"


class GameState: public State
{
public:

                        GameState(sf::RenderWindow& window, 
                                  const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                                  std::stack<State*>* const pStates
                                  );
    virtual             ~GameState();

    virtual void        processEvent(const sf::Event& event);
    void                processPauseMenuButtonsEvent(const sf::Event& event);

    virtual void        update(const float deltaTime);
    void                updateView();
    void                updatePlayerKeyboardInput(const float deltaTime);
    void                updateTilemap(const float deltaTime);
    void                updatePlayerGUI();
    void                updateEnemiesAndCombat(const float deltaTime);
    void                updateCombat(Enemy& enemy);

    virtual void        render(sf::RenderTarget* pTarget = nullptr);
    void                renderEnemies(sf::RenderTarget& target);

private:

    std::list<Enemy*>   enemies;
    EnemySystem*        pEnemySystem;
    TextTagSystem*      pTextTagSystem;

    sf::View            view;
    sf::RenderTexture   renderTexture;
    sf::Sprite          renderSprite;
    Tilemap*            pTilemap;

    Player*             pPlayer;
    PlayerGUI*          pPlayerGUI;
    Inventory           playerInventory;
    Weapon*             pPlayerActiveWeapon;

    PauseMenu*          pPauseMenu;
    sf::Font            font;
    sf::Shader          coreShader;


    void                initView();
    void                initRenderTexture();
    void                initTilemap();
    virtual void        initTextures();
    void                initPlayer();
    void                initPlayerGUI();
    void                initPlayerInventory();
    void                initPauseMenu();
    void                initShader();
    void                initSystems();

};


#endif // GAMESTATE_H
