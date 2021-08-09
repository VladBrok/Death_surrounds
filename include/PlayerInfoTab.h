#ifndef PLAYERINFOTAB_H
#define PLAYERINFOTAB_H

#include "InfoTab.h"
#include "Player.h"


class PlayerInfoTab: public InfoTab
{
public:

                    PlayerInfoTab(const sf::RenderWindow& window, const sf::Font& font, const Player& player);
    virtual void    update();

private:

    const Player&   player;
    virtual void    initInfoTab(const sf::RenderWindow& window, const sf::Font& font);

};


#endif // PLAYERINFOTAB_H
