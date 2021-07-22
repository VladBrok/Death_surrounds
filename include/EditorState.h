#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Button.h"
#include "PauseMenu.h"
#include "TileMap.h"


class EditorState: public State
{
public:

                                             EditorState(sf::RenderWindow& window, 
                                                         const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                                                         std::stack<State*>* const pStates
                                                         );
    virtual                                  ~EditorState();

    virtual void                             processEvents(const sf::Event& event);
    void                                     processPauseMenuButtonEvents(const sf::Event& event);
    virtual void                             update(const float deltaTime);
    void                                     updateTileSelector();
    virtual void                             render(sf::RenderTarget* pTarget = nullptr);
    void                                     renderButtons(sf::RenderTarget& target);

private:

    sf::Font                                 font;
    PauseMenu*                               pPauseMenu;
    std::unordered_map<std::string, Button*> buttons;
    TileMap                                  tileMap;
    sf::RectangleShape                       tileSelector;

    void                                     initFont();
    void                                     initButtons();
    virtual void                             initTextures();
    void                                     initPauseMenu();
    void                                     initTileSelector();
};


#endif // EDITORSTATE_H
