#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"
#include "ProgressBar.h"
#include "PlayerInfoTab.h"


class PlayerGui: public sf::NonCopyable
{
public:

                      PlayerGui(Player& player, const sf::RenderWindow& window);
                      ~PlayerGui();
    void              update();
    void              render(sf::RenderTarget& target);

    // Hides the player's info tab if it's shown and vice versa
    void              toggleInfoTab();
                      
private:              
                      
    Player&           player;
    sf::Font          font;
                      
    PlayerInfoTab*    pPlayerInfoTab;
    ProgressBar       levelBox;
    ProgressBar       hpBar;
    ProgressBar       expBar;
                      
                      
    void              initFont();
    void              initGui(const sf::RenderWindow& window);
};


#endif // PLAYERGUI_H
