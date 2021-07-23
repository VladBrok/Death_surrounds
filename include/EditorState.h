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
    void                                     processPauseMenuButtonsEvent(const sf::Event& event);
    void                                     processButtonsEvent(const sf::Event& event);
    void                                     processEditorEvent(const sf::Event& event);

    void                                     updateTileSelector();

    virtual void                             render(sf::RenderTarget* pTarget = nullptr);
    void                                     renderButtons(sf::RenderTarget& target);

private:

    sf::Font                                 font;
    PauseMenu*                               pPauseMenu;
    std::unordered_map<std::string, Button*> buttons;
    TileMap                                  tileMap;
    sf::RectangleShape                       tileSelector;
    TextureSelector                          textureSelector;
    sf::IntRect                              textureRect;

    void                                     initFont();
    void                                     initButtons();
    virtual void                             initTextures();
    void                                     initPauseMenu();
    void                                     initTextureRect();
    void                                     initTileSelector();
};


#endif // EDITORSTATE_H
