#include "precompiled.h"
#include "PlayerGUI.h"
#include "Utils.h"
#include "Resources.h"


PlayerGui::PlayerGui(const Player& player, 
                     const sf::Font& font,
                     const sf::RenderWindow& window,
                     const sf::Texture& hpBarTexture,
                     const sf::Texture& expBarTexture
                     )
    : player(player)
{
    initGui(window, font, hpBarTexture, expBarTexture);
}


PlayerGui::~PlayerGui()
{
    delete pPlayerInfoTab;
}


void PlayerGui::update()
{
    hpBar.update(player.getHp(), player.getHpMax());
    expBar.update(player.getExp(), player.getExpForNextLevel());

    if (!pPlayerInfoTab->isHidden())
    {
        pPlayerInfoTab->update();
    }
}


void PlayerGui::render(sf::RenderTarget& target)
{
    hpBar.render(target);
    expBar.render(target);
    pPlayerInfoTab->render(target);
}


void PlayerGui::toggleInfoTab()
{
    pPlayerInfoTab->toggle();
}


void PlayerGui::initGui(const sf::RenderWindow& window,
                        const sf::Font& font,
                        const sf::Texture& hpBarTexture,
                        const sf::Texture& expBarTexture
                        )
{

    /*=============== Progress bars ===============*/
    
    hpBar.create(
        utils::percentToPixels(3.f, window.getSize().x),
        utils::percentToPixels(3.f, window.getSize().x),
        hpBarTexture.getSize().x,
        hpBarTexture.getSize().y,
        hpBarTexture,
        sf::Color(50, 50, 50, 150)
    );

    expBar.create(
        hpBar.getPosition().x + hpBar.getBackSize().x / 2.f - expBarTexture.getSize().x / 2.f,
        hpBar.getPosition().y + hpBar.getBackSize().y + utils::percentToPixels(1.3f, window.getSize().y),
        expBarTexture.getSize().x,
        expBarTexture.getSize().y,
        expBarTexture,
        sf::Color(50, 50, 50, 150)
    );  


    /*=============== Player info tab ===============*/

    pPlayerInfoTab = new PlayerInfoTab(window, font, player);
}
