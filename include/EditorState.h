#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Button.h"


class EditorState: public State
{
public:

                                                EditorState(sf::RenderWindow* pWindow, 
                                                              const std::unordered_map<std::string, 
                                                              sf::Keyboard::Key>* const pSupportedKeys,
                                                              std::stack<State*>* const pStates
                                                              );
    virtual                                     ~EditorState();

    virtual void                                update(const float deltaTime);
    virtual void                                updateKeyboardInput(const float deltaTime);
    virtual void                                render(sf::RenderTarget* pTarget = nullptr);

    void                                        updateButtons();
    void                                        renderButtons();

private:

    sf::Font                                    font;
    std::unordered_map<std::string, Button*>    buttons;

    void                                        initFont();
    void                                        initButtons();
    virtual void                                initTextures();
};


#endif // EDITORSTATE_H
