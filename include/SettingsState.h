#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "Button.h"
#include "DropDownList.h"


class SettingsState: public State
{
public:

                               SettingsState(sf::RenderWindow& window, 
                                             const StringToKeyMap& supportedKeys,
                                             std::stack<State*>& states,
                                             bool& settingsChanged
                                             );
    virtual                    ~SettingsState();
                               
    virtual void               processEvent(const sf::Event& event);
    virtual void               render(sf::RenderTarget* pTarget = nullptr);
    void                       renderGui(sf::RenderTarget& target);
    void                       renderOptionsText(sf::RenderTarget& target);
                               
private:                       
                               
    sf::RectangleShape         background;
    sf::Text                   optionsText;
    StringToButtonMap          buttons;
    StringToDropDownListMap    dropDownLists;
    bool&                      settingsChanged;
                               
    void                       initGui();
    void                       initBackground();
    void                       initOptionsText();

    // String example: 800 x 600
    sf::Vector2i               getResolutionFromString(const std::string& string);

    // Reinitialization of the gui and background
    void                       reinitialize();
};


#endif // SETTINGSSTATE_H
