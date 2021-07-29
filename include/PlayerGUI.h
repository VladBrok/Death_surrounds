#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"


class PlayerGUI: public sf::NonCopyable
{
public:

                            PlayerGUI(Player& player, const sf::RenderWindow& window);
    void                    update();
    void                    render(sf::RenderTarget& target);
                           
private:                   
                           
    Player*                 pPlayer;
    sf::Font                font;

    sf::RectangleShape      levelBox;
    sf::Text                levelBoxText;

    sf::RectangleShape      hpBarBack;
    sf::RectangleShape      hpBarInner;
    sf::Text                hpBarText;

    sf::RectangleShape      expBarBack;
    sf::RectangleShape      expBarInner;
    sf::Text                expBarText;


    void                    initFont();
    void                    initLevelBox(const sf::RenderWindow& window);
    void                    initHPBar(const sf::RenderWindow& window);
    void                    initExpBar(const sf::RenderWindow& window);

    void                    updateLevelBox();
    void                    updateHPBar();
    void                    updateExpBar();

    void                    renderLevelBox(sf::RenderTarget& target);
    void                    renderHPBar(sf::RenderTarget& target);
    void                    renderExpBar(sf::RenderTarget& target);

};


#endif // PLAYERGUI_H
