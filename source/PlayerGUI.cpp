#include "precompiled.h"
#include "PlayerGUI.h"


PlayerGUI::PlayerGUI(Player& player, const sf::RenderWindow& window)
    : pPlayer(&player)
{
    initFont();
    initHPBar(window);
}


void PlayerGUI::update()
{
    updateHPBar();
}


void PlayerGUI::render(sf::RenderTarget& target)
{
    renderHPBar(target);
}


void PlayerGUI::initFont()
{
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
}


void PlayerGUI::initHPBar(const sf::RenderWindow& window)
{
    const sf::Vector2f barSize(window.getSize().x / 8.f, window.getSize().x / 30.f);
    const sf::Vector2f barPosition(window.getSize().x / 32.f, window.getSize().x / 32.f);

    hpBarBack.setSize(barSize);
    hpBarBack.setPosition(barPosition);
    hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));

    hpBarInner.setSize(barSize);
    hpBarInner.setPosition(barPosition);
    hpBarInner.setFillColor(sf::Color(250, 0, 0, 190));

    hpBarText.setFont(font);
    hpBarText.setCharacterSize(barSize.y / 1.5f);
    hpBarText.setPosition(barPosition.x, barPosition.y);
}


void PlayerGUI::updateHPBar()
{
    // Ratio of the hp and the max hp
    float ratio = static_cast<float>(pPlayer->getHP()) / static_cast<float>(pPlayer->getHPMax());

    // Updating the width of the inner hp bar using the ratio
    hpBarInner.setSize(
        sf::Vector2f(
            hpBarBack.getSize().x * ratio, 
            hpBarInner.getSize().y
        )
    );

    hpBarText.setString(
        std::to_string((long long)pPlayer->getHP()) + " / " + 
        std::to_string((long long)pPlayer->getHPMax())
    );
}


void PlayerGUI::renderHPBar(sf::RenderTarget& target)
{
    target.draw(hpBarBack);
    target.draw(hpBarInner);
    target.draw(hpBarText);
}