#ifndef PLAYERINFOTAB_H
#define PLAYERINFOTAB_H

#include "InfoTab.h"
#include "Player.h"


class PlayerInfoTab: public InfoTab
{
public:

                    PlayerInfoTab(const sf::RenderWindow& window, const sf::Font& font, Player& player);
    virtual void    update();

private:

    Player&         player;
    virtual void    initInfoTab(const sf::RenderWindow& window, const sf::Font& font);

};


#endif // PLAYERINFOTAB_H
