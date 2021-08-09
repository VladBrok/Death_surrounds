#include "precompiled.h"
#include "PlayerInfoTab.h"
#include "Utils.h"


PlayerInfoTab::PlayerInfoTab(const sf::RenderWindow& window, const sf::Font& font, const Player& player)
    : InfoTab(), player(player)
{
    initInfoTab(window, font);
}


void PlayerInfoTab::update()
{
   tabText.setString(player.getStatsAsString());
}


void PlayerInfoTab::initInfoTab(const sf::RenderWindow& window, const sf::Font& font)
{
    tabBackground.setFillColor(sf::Color(50, 50, 50, 200));
    tabBackground.setOutlineColor(sf::Color(30, 30, 30, 220));
    tabBackground.setOutlineThickness(3.f);
    tabBackground.setSize(
        sf::Vector2f(
            utils::percentToPixels(45.f, window.getSize().x), 
            (float)window.getSize().y
        )
    );

    tabText.setFont(font);
    tabText.setCharacterSize((unsigned)utils::percentToPixels(2.8f, tabBackground.getSize().x + tabBackground.getSize().y));
    tabText.setPosition(
        (float)(int)(tabBackground.getPosition().x + utils::percentToPixels(20.f, tabBackground.getSize().x)),
        (float)(int)(tabBackground.getPosition().y + utils::percentToPixels(18.f, tabBackground.getSize().y))
    );
}