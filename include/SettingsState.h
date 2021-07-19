#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "State.h"
#include "Button.h"


class SettingsState: public State
{
public:

                                             SettingsState(sf::RenderWindow& window, 
                                                           const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                                                           std::stack<State*>* const pStates
                                                           );
    virtual                                  ~SettingsState();
                                             
    virtual void                             update(const float deltaTime);
    virtual void                             updateKeyboardInput(const float deltaTime);
    virtual void                             render(sf::RenderTarget* pTarget = nullptr);
                                             
    void                                     updateButtons();
    void                                     renderButtons();

private:

    sf::RectangleShape                       background;
    sf::Font                                 font;
    std::unordered_map<std::string, Button*> buttons;

    void                                     initFont();
    void                                     initButtons();
    void                                     initBackground();
    virtual void                             initTextures();
};


#endif // SETTINGS_STATE_H
