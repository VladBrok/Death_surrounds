#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"
#include "Button.h"


class MainMenuState: public State
{
public:

                                             MainMenuState(sf::RenderWindow& window, 
                                                           const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                                                           std::stack<State*>* const pStates
                                                           );
    virtual                                  ~MainMenuState();
    
    virtual void                             processEvent(const sf::Event& event);
    virtual void                             render(sf::RenderTarget* pTarget = nullptr);
                                             
    void                                     renderButtons(sf::RenderTarget& target);

private:

    sf::RectangleShape                       background;
    sf::Font                                 font;
    std::unordered_map<std::string, Button*> buttons;

    void                                     initFont();
    void                                     initButtons();
    void                                     initBackground();
    virtual void                             initTextures();
};


#endif // MAIN_MENU_STATE_H
