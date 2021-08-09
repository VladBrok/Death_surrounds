#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"
#include "Button.h"


class MainMenuState: public State
{
public:

                                             MainMenuState(sf::RenderWindow& window, 
                                                           const std::unordered_map<std::string, sf::Keyboard::Key>& supportedKeys,
                                                           std::stack<State*>& states
                                                           );
    virtual                                  ~MainMenuState();
    
    virtual void                             processEvent(const sf::Event& event);
    virtual void                             render(sf::RenderTarget* pTarget = nullptr);
                                             
    void                                     renderGui(sf::RenderTarget& target);

private:

    sf::RectangleShape                       background;
    sf::Font                                 font;
    std::unordered_map<std::string, Button*> buttons;

    void                                     initFont();
    void                                     initGui();
    void                                     initBackground();
    virtual void                             initTextures();

    // Reinitialization of the buttons and background
    void                                     reinitialize();
};


#endif // MAIN_MENU_STATE_H
