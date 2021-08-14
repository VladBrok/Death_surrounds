#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "typedefs.h"


class PauseMenu: public sf::NonCopyable
{
public:

                          PauseMenu(const sf::RenderWindow& window, sf::Font& font);
                          ~PauseMenu();
    void                  processEvent(const sf::Event& event, 
                                       const sf::Vector2i& mousePosWindow
                                       );
    void                  render(sf::RenderTarget& target);
    void                  addButton(const std::string& buttonKey, 
                                    const std::string& buttonText,
                                    const int verticalPositionFrom1To5
                                    );
    bool                  isButtonPressed(const std::string& buttonKey) const;
                          
private:                  
                          
    sf::RectangleShape    background;
    sf::RectangleShape    menuContainer;
    StringToButtonMap     buttons; 
    sf::Text              text;
    sf::Font&             font;
                          
    void                  initText(const sf::RenderWindow& window);
};


#endif // PAUSEMENU_H
