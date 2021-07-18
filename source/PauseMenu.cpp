#include "PauseMenu.h"


PauseMenu::PauseMenu(const sf::RenderWindow& window)
    : background(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y)),
      menu(sf::Vector2f(window.getSize().x / 3.f, window.getSize().y / 1.3f))
{
    menu.setPosition(
        window.getSize().x / 2.f - menu.getSize().x / 2.f,
        window.getSize().y / 2.f - menu.getSize().y / 2.f
    );

    menu.setFillColor(sf::Color(20, 20, 20, 200));
    background.setFillColor(sf::Color(20, 20, 20, 100));
}


PauseMenu::~PauseMenu()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        delete b->second;
    }
}


void PauseMenu::render(sf::RenderTarget& target)
{
    target.draw(background);
    target.draw(menu);

    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(target);
    }
}