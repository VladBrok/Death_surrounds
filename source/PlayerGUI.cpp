#include "precompiled.h"
#include "PlayerGUI.h"
#include "GUI_functions.h"


PlayerGUI::PlayerGUI(Player& player, const sf::RenderWindow& window)
    : pPlayer(&player)
{
    initFont();
    initLevelBox(window);
    initHPBar(window);
    initExpBar(window);
}


void PlayerGUI::update()
{
    updateLevelBox();
    updateHPBar();
    updateExpBar();
}


void PlayerGUI::render(sf::RenderTarget& target)
{
    renderLevelBox(target);
    renderHPBar(target);
    renderExpBar(target);
}


void PlayerGUI::initFont()
{
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
}


void PlayerGUI::initLevelBox(const sf::RenderWindow& window)
{
    const sf::Vector2f boxSize(
                          gui::percentToPixels(3.3f, window.getSize().x), 
                          gui::percentToPixels(3.3f, window.getSize().x)
                       );
    const sf::Vector2f boxPosition(
                          gui::percentToPixels(3.f, window.getSize().x), 
                          gui::percentToPixels(3.f, window.getSize().x)
                       );

    levelBox.setSize(boxSize);
    levelBox.setPosition(boxPosition);
    levelBox.setFillColor(sf::Color(50, 50, 50, 200));

    levelBoxText.setFont(font);
    levelBoxText.setCharacterSize(boxSize.y / 2.5f);
    levelBoxText.setString(std::to_string((long long)1));
    levelBoxText.setPosition(
        (int)(boxPosition.x + boxSize.x / 2.f - levelBoxText.getGlobalBounds().width), 
        (int)(boxPosition.y + boxSize.y / 2.f - levelBoxText.getGlobalBounds().height)
    );
}


void PlayerGUI::initHPBar(const sf::RenderWindow& window)
{
    const sf::Vector2f barSize(gui::percentToPixels(13.f, window.getSize().x), levelBox.getSize().y);
    const sf::Vector2f barPosition(
        levelBox.getPosition().x,
        levelBox.getPosition().y + levelBox.getSize().y + gui::percentToPixels(1.3f, window.getSize().y)
    );

    hpBarBack.setSize(barSize);
    hpBarBack.setPosition(barPosition);
    hpBarBack.setFillColor(levelBox.getFillColor());

    hpBarInner.setSize(barSize);
    hpBarInner.setPosition(barPosition);
    hpBarInner.setFillColor(sf::Color(250, 0, 0, 190));

    hpBarText.setFont(font);
    hpBarText.setCharacterSize(barSize.y / 2.5f);
    hpBarText.setString("0 / 0");
    hpBarText.setPosition(
        (int)(barPosition.x + gui::percentToPixels(0.7f, window.getSize().x)), 
        (int)(barPosition.y + barSize.y / 2.f - hpBarText.getGlobalBounds().height / 1.8f)
    );
}


void PlayerGUI::initExpBar(const sf::RenderWindow& window)
{
    const sf::Vector2f barSize(hpBarBack.getSize().x, hpBarBack.getSize().y);
    const sf::Vector2f barPosition(
        hpBarBack.getPosition().x, 
        hpBarBack.getPosition().y + hpBarBack.getSize().y + 10.f
    );

    expBarBack.setSize(barSize);
    expBarBack.setPosition(barPosition);
    expBarBack.setFillColor(levelBox.getFillColor());

    expBarInner.setSize(barSize);
    expBarInner.setPosition(barPosition);
    expBarInner.setFillColor(sf::Color(0, 0, 250, 190));

    expBarText.setFont(font);
    expBarText.setCharacterSize(barSize.y / 2.5f);
    expBarText.setString("0 / 0");
    expBarText.setPosition(
        (int)(barPosition.x + gui::percentToPixels(0.7f, window.getSize().x)), 
        (int)(barPosition.y + barSize.y / 2.f - expBarText.getGlobalBounds().height / 1.8f)
    );
}


void PlayerGUI::updateLevelBox()
{
    levelBoxText.setString(std::to_string((long long)pPlayer->getLevel()));
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


void PlayerGUI::updateExpBar()
{
    // Ratio of the current experience and the experience required for the next level
    float ratio = static_cast<float>(pPlayer->getExp()) / static_cast<float>(pPlayer->getExpForNextLevel());

    // Updating the width of the inner exp bar using the ratio
    expBarInner.setSize(
        sf::Vector2f(
            expBarBack.getSize().x * ratio, 
            expBarInner.getSize().y
        )
    );

    expBarText.setString(
        std::to_string((long long)pPlayer->getExp()) + " / " + 
        std::to_string((long long)pPlayer->getExpForNextLevel())
    );
}


void PlayerGUI::renderLevelBox(sf::RenderTarget& target)
{
    target.draw(levelBox);
    target.draw(levelBoxText);
}


void PlayerGUI::renderHPBar(sf::RenderTarget& target)
{
    target.draw(hpBarBack);
    target.draw(hpBarInner);
    target.draw(hpBarText);
}


void PlayerGUI::renderExpBar(sf::RenderTarget& target)
{
    target.draw(expBarBack);
    target.draw(expBarInner);
    target.draw(expBarText);
}