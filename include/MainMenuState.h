#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"
#include "Button.h"


class MainMenuState: public State
{
public:
                          
                          MainMenuState(sf::RenderWindow& window, 
                                        const StringToKeyMap& supportedKeys,
                                        std::stack<std::unique_ptr<State>>& states
                                        );
                          
    virtual void          processEvent(const sf::Event& event);
    virtual void          render(sf::RenderTarget* pTarget = nullptr);
                          
private:                  
                          
    sf::RectangleShape    background;
    StringToButtonMap     buttons;
    bool                  needToReinitialize;

    void                  renderGui(sf::RenderTarget& target);

    void                  initGui();
    void                  initBackground();
    virtual void          initTextures();

    // Reinitialization of the buttons and background
    void                  reinitialize();
};


#endif // MAIN_MENU_STATE_H
