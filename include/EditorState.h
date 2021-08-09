#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Button.h"
#include "PauseMenu.h"
#include "Tilemap.h"
#include "TextureSelector.h"
#include "EditorMode.h"
#include "DefaultEditorMode.h"


class EditorState: public State
{
public:

                                         EditorState(sf::RenderWindow& window, 
                                                     const std::unordered_map<std::string, sf::Keyboard::Key>& supportedKeys,
                                                     std::stack<State*>& states
                                                     );
    virtual                              ~EditorState();

    virtual void                         processEvent(const sf::Event& event);
    virtual void                         update(const float deltaTime);
    virtual void                         render(sf::RenderTarget* pTarget = nullptr);

private:

    sf::View                             view;
    std::vector<EditorMode*>             modes;
    sf::Font                             font;
    PauseMenu*                           pPauseMenu;
    Tilemap                              tilemap;
    int                                  activeMode;
  
    void                                 processPauseMenuEvent(const sf::Event& event);
    void                                 processKeyboardEvent(const sf::Event& event);

    void                                 initView();  
    void                                 initFont();
    void                                 initModes();
    void                                 initGui();

};


#endif // EDITORSTATE_H
