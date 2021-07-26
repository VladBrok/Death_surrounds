#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Player.h"
#include "PauseMenu.h"
#include "Tilemap.h"


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
    virtual void        render(sf::RenderTarget* pTarget = nullptr);

private:

    sf::View            view;
    sf::RenderTexture   renderTexture;
    sf::Sprite          renderSprite;
    Tilemap*            pTilemap;
    Player*             pPlayer;
    PauseMenu*          pPauseMenu;
    sf::Font            font;

    void                initView();
    void                initRenderTexture();
    void                initTilemap();
    virtual void        initTextures();
    void                initPlayer();
    void                initPauseMenu();

};


#endif // GAMESTATE_H
