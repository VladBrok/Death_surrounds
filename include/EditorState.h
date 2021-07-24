#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Button.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "TextureSelector.h"


class EditorState: public State
{
public:

                                             EditorState(sf::RenderWindow& window, 
                                                         const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                                                         std::stack<State*>* const pStates
                                                         );
    virtual                                  ~EditorState();

    virtual void                             processEvent(const sf::Event& event);
    void                                     processPauseMenuEvent(const sf::Event& event);
    void                                     processButtonsEvent(const sf::Event& event);
    void                                     processTileMapEvent(const sf::Event& event);
    void                                     processTextureSelectorEvent(const sf::Event& event);

    void                                     updateSideBarActivity();

    virtual void                             render(sf::RenderTarget* pTarget = nullptr);
    void                                     renderPauseMenu(sf::RenderTarget& target);
    void                                     renderButtons(sf::RenderTarget& target);
    void                                     renderTileSelector(sf::RenderTarget& target);
    void                                     renderTextureSelector(sf::RenderTarget& target);

private:

    sf::Font                                 font;
    PauseMenu*                               pPauseMenu;
    std::unordered_map<std::string, Button*> buttons;
    TileMap                                  tileMap;
    sf::RectangleShape                       tileSelector;
    TextureSelector*                         pTextureSelector;
    sf::IntRect                              textureRect;
    sf::RectangleShape                       sideBar;
    bool                                     sideBarIsActive;
    bool                                     hideTextureSelector;
    
    virtual void                             initTextures();
    void                                     initFont();
    void                                     initSideBar();
    void                                     initButtons();
    void                                     initPauseMenu();
    void                                     initTextureRect();
    void                                     initTileAndTextureSelectors();
};


#endif // EDITORSTATE_H
