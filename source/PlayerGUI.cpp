#include "precompiled.h"
#include "PlayerGUI.h"
#include "Utils.h"
#include "Resources.h"


PlayerGui::PlayerGui(Player& player, const sf::RenderWindow& window)
    : player(player)
{
    initFont();
    initGui(window);
}


PlayerGui::~PlayerGui()
{
    delete pPlayerInfoTab;
}


void PlayerGui::update()
{
    hpBar.update(player.getHP(), player.getHPMax());
    expBar.update(player.getExp(), player.getExpForNextLevel());
    levelBox.setTextString(std::to_string((long long)player.getLevel()));
    pPlayerInfoTab->update();
}


void PlayerGui::render(sf::RenderTarget& target)
{
    hpBar.render(target);
    expBar.render(target);
    levelBox.render(target);
    pPlayerInfoTab->render(target);
}


void PlayerGui::toggleInfoTab()
{
    pPlayerInfoTab->toggle();
}


void PlayerGui::initFont()
{
    font.loadFromFile(resources::getFontFile());
}


void PlayerGui::initGui(const sf::RenderWindow& window)
{
    // Progress bars

    levelBox.create(
        utils::percentToPixels(3.f, window.getSize().x),
        utils::percentToPixels(3.f, window.getSize().x),
        utils::percentToPixels(3.3f, window.getSize().x),
        utils::percentToPixels(3.3f, window.getSize().x),
        font,
        sf::Color(50, 50, 50, 200),
        sf::Color::Transparent,
        true,
        "1"
    );

    hpBar.create(
        levelBox.getPosition().x, 
        levelBox.getPosition().y + levelBox.getBackSize().y + utils::percentToPixels(1.3f, window.getSize().y), 
        utils::percentToPixels(13.f, window.getSize().x),
        levelBox.getBackSize().y, 
        font, 
        sf::Color(250, 0, 0, 190),
        sf::Color(50, 50, 50, 200)
    );

    expBar.create(
        hpBar.getPosition().x,
        hpBar.getPosition().y + hpBar.getBackSize().y + utils::percentToPixels(1.3f, window.getSize().y),
        hpBar.getBackSize().x,
        hpBar.getBackSize().y,
        font,
        sf::Color(0, 0, 250, 190),
        sf::Color(50, 50, 50, 200)
    );  


    // Player info tab

    pPlayerInfoTab = new PlayerInfoTab(window, font, player);
}
