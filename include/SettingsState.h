#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "State.h"
#include "Button.h"
#include "DropDownList.h"


class SettingsState: public State
{
public:

                                                   SettingsState(sf::RenderWindow& window, 
                                                                 const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                                                                 std::stack<State*>* const pStates
                                                                 );
    virtual                                        ~SettingsState();
    
    virtual void                                   processEvent(const sf::Event& event);
    virtual void                                   render(sf::RenderTarget* pTarget = nullptr);
    void                                           renderGui(sf::RenderTarget& target);

private:

    sf::RectangleShape                             background;
    sf::Font                                       font;
    std::unordered_map<std::string, Button*>       buttons;
    std::unordered_map<std::string, DropDownList*> dropDownLists;

    void                                           initFont();
    void                                           initGui();
    void                                           initBackground();
    virtual void                                   initTextures();

    sf::Vector2i                                   getResolutionFromString(const std::string& string); // String example: 800 x 600
};


#endif // SETTINGS_STATE_H
