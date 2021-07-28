#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"


class PlayerGUI
{
public:

                            PlayerGUI(Player& player, const sf::RenderWindow& window);
    void                    update();
    void                    render(sf::RenderTarget& target);
                           
private:                   
                           
    Player*                 pPlayer;
    sf::Font                font;
    sf::RectangleShape      hpBarBack;
    sf::RectangleShape      hpBarInner;
    sf::Text                hpBarText;

    void                    initFont();
    void                    initHPBar(const sf::RenderWindow& window);

    void                    updateHPBar();
    void                    renderHPBar(sf::RenderTarget& target);
};


#endif // PLAYERGUI_H
