#include "precompiled.h"
#include "ErrorWindow.h"
#include "Utils.h"


ErrorWindow::ErrorWindow(const std::string& info,
                         const bool showCancelButton
                         )
    : InfoWindow("", info, showCancelButton)
{
    errorText.setFont(font);
    errorText.setCharacterSize((unsigned)utils::percentToPixels(4.f, (int)(window.getSize().x + window.getSize().y)));
    errorText.setColor(sf::Color::Red);
    errorText.setStyle(sf::Text::Bold);
    errorText.setString("ERROR!");
    errorText.setPosition(
        std::floor(window.getSize().x / 2u - errorText.getGlobalBounds().width / 2.f),
        utils::percentToPixels(1.f, (int)window.getSize().y)
    );
}



void ErrorWindow::render()
{
    InfoWindow::render();

    window.draw(errorText);
}