#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"
#include "ProgressBar.h"
#include "PlayerInfoTab.h"


class PlayerGui: public sf::NonCopyable
{
public:

                       PlayerGui(const Player& player, 
                                 const sf::Font& font,
                                 const sf::RenderWindow& window,
                                 const sf::Texture& hpBarTexture,
                                 const sf::Texture& expBarTexture
                                 );
                       ~PlayerGui();
    void               update();
    void               render(sf::RenderTarget& target);

    // Hides the player's info tab if it's shown and vice versa
    void               toggleInfoTab();
                      
private:              
                      
    const Player&      player;
                      
    PlayerInfoTab*     pPlayerInfoTab;
    ProgressBar        hpBar;
    ProgressBar        expBar;
                       
                       
    void               initGui(const sf::RenderWindow& window,
                               const sf::Font& font,
                               const sf::Texture& hpBarTexture,
                               const sf::Texture& expBarTexture
                               );
};


#endif // PLAYERGUI_H
