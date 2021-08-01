#include "precompiled.h"
#include "PlayerGUI.h"
#include "GUI_functions.h"


PlayerGUI::PlayerGUI(Player& player, const sf::RenderWindow& window)
    : pPlayer(&player)
{
    initFont();


    levelBox.create(
        gui::percentToPixels(3.f, window.getSize().x),
        gui::percentToPixels(3.f, window.getSize().x),
        gui::percentToPixels(3.3f, window.getSize().x),
        gui::percentToPixels(3.3f, window.getSize().x),
        font,
        sf::Color(50, 50, 50, 200),
        sf::Color::Transparent,
        true,
        "1"
    );

    hpBar.create(
        levelBox.getPosition().x, 
        levelBox.getPosition().y + levelBox.getBackSize().y + gui::percentToPixels(1.3f, window.getSize().y), 
        gui::percentToPixels(13.f, window.getSize().x),
        levelBox.getBackSize().y, 
        font, 
        sf::Color(250, 0, 0, 190),
        sf::Color(50, 50, 50, 200)
    );

    expBar.create(
        hpBar.getPosition().x,
        hpBar.getPosition().y + hpBar.getBackSize().y + gui::percentToPixels(1.3f, window.getSize().y),
        hpBar.getBackSize().x,
        hpBar.getBackSize().y,
        font,
        sf::Color(0, 0, 250, 190),
        sf::Color(50, 50, 50, 200)
    );   
}


void PlayerGUI::update()
{
    hpBar.update(pPlayer->getHP(), pPlayer->getHPMax());
    expBar.update(pPlayer->getExp(), pPlayer->getExpForNextLevel());
    levelBox.setTextString(std::to_string((long long)pPlayer->getLevel()));
}


void PlayerGUI::render(sf::RenderTarget& target)
{
    hpBar.render(target);
    expBar.render(target);
    levelBox.render(target);
}


void PlayerGUI::initFont()
{
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
}
