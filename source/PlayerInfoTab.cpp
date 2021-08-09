#include "precompiled.h"
#include "PlayerInfoTab.h"
#include "Utils.h"


PlayerInfoTab::PlayerInfoTab(const sf::RenderWindow& window, const sf::Font& font, Player& player)
    : InfoTab(), player(player)
{
    initInfoTab(window, font);
}


void PlayerInfoTab::update()
{
   
}


void PlayerInfoTab::initInfoTab(const sf::RenderWindow& window, const sf::Font& font)
{
    tabBackground.setFillColor(sf::Color(50, 50, 50, 180));
    tabBackground.setOutlineColor(sf::Color(30, 30, 30, 210));
    tabBackground.setOutlineThickness(3.f);
    tabBackground.setSize(
        sf::Vector2f(
            utils::percentToPixels(45.f, window.getSize().x), 
            (float)window.getSize().y
        )
    );

    tabText.setFont(font);
    tabText.setCharacterSize((unsigned)utils::percentToPixels(1.2f, window.getSize().x + window.getSize().y));
    tabText.setPosition(
        tabBackground.getPosition().x + utils::percentToPixels(3.f, window.getSize().x),
        tabBackground.getPosition().y
    );
    tabText.setString("TEST");
}