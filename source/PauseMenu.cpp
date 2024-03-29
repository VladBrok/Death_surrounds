#include "precompiled.h"
#include "PauseMenu.h"
#include "Button.h"


PauseMenu::PauseMenu(const sf::RenderWindow& window, sf::Font& font)
    : background(sf::Vector2f(window.getSize())),
      menuContainer(sf::Vector2f(window.getSize().x / 3.f, window.getSize().y / 1.12f)),
      font(font)
{
    menuContainer.setPosition(
        window.getSize().x / 2.f - menuContainer.getSize().x / 2.f,
        window.getSize().y / 2.f - menuContainer.getSize().y / 2.f
    );

    menuContainer.setFillColor(sf::Color(20, 20, 20, 210));
    background.setFillColor(sf::Color(20, 20, 20, 110));

    initText(window);
}


void PauseMenu::processEvent(const sf::Event& event, const sf::Vector2i& mousePosWindow)
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->processEvent(event, mousePosWindow);
    }
}


void PauseMenu::render(sf::RenderTarget& target)
{
    target.draw(background);
    target.draw(menuContainer);
    target.draw(text);

    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(target);
    }
}


void PauseMenu::addButton(const std::string& buttonKey,
                          const std::string& buttonText,
                          const int verticalPositionFrom1To5
                          )
{
    assert(verticalPositionFrom1To5 >= 1 && verticalPositionFrom1To5 <= 5);

    const sf::Vector2f buttonSize(
        static_cast<float>(menuContainer.getSize().x / 2),
        static_cast<float>(menuContainer.getSize().y / 8)
    );
    const sf::Color textIdleColor(sf::Color(150, 150, 150));
    const sf::Color textHoverColor(sf::Color::White);
    const sf::Color textActiveColor(sf::Color(20, 20, 20, 200));

    buttons[buttonKey].reset(new Button(std::floor(menuContainer.getPosition().x + menuContainer.getSize().x / 2.f - buttonSize.x / 2.f),
                                    std::floor(verticalPositionFrom1To5 * (menuContainer.getSize().y / 7.f) + text.getGlobalBounds().height * 2.3f), 
                                    buttonSize.x, 
                                    buttonSize.y,
                                    font, 
                                    buttonText,
                                    textIdleColor,
                                    textHoverColor,
                                    textActiveColor
                                    ));
}


bool PauseMenu::isButtonPressed(const std::string& buttonKey) const
{
    return buttons.at(buttonKey)->isPressed(false);
}


void PauseMenu::initText(const sf::RenderWindow& window)
{
    text.setFont(font);
    text.setCharacterSize(window.getSize().x / 19);
    text.setString("PAUSE");
    text.setPosition(
        menuContainer.getPosition().x + menuContainer.getSize().x / 2.f - text.getGlobalBounds().width / 2.f,
        menuContainer.getPosition().y + menuContainer.getSize().y / 12.f
    );
    text.setStyle(sf::Text::Bold);
}