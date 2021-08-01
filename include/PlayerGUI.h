#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"
#include "ProgressBar.h"


class PlayerGUI: public sf::NonCopyable
{
public:

                            PlayerGUI(Player& player, const sf::RenderWindow& window);
    void                    update();
    void                    render(sf::RenderTarget& target);
                           
private:                   
                           
    Player*                 pPlayer;
    sf::Font                font;

    ProgressBar             levelBox;
    ProgressBar             hpBar;
    ProgressBar             expBar;


    void                    initFont();
};


#endif // PLAYERGUI_H
