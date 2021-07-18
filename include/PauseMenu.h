#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "SFML\Graphics.hpp"
#include "Button.h"
#include <unordered_map>


class PauseMenu
{
public:

                                             PauseMenu(const sf::RenderWindow& window);
                                             ~PauseMenu();
    void                                     render(sf::RenderTarget& target);

private:

    sf::RectangleShape                       background;
    sf::RectangleShape                       menu;
    std::unordered_map<std::string, Button*> buttons; 

};


#endif // PAUSEMENU_H
