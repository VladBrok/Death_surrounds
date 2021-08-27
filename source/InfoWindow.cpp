#include "precompiled.h"
#include "InfoWindow.h"
#include "constants.h"
#include "Utils.h"
#include "Resources.h"


InfoWindow::InfoWindow(const std::string& title, 
                       const std::string& info,
                       const bool showCancelButton
                       )
                       : SHOW_CANCEL_BUTTON(showCancelButton)
{
    font.loadFromFile(resources::getFontFile());

    const sf::Vector2u size(
        (unsigned)(sf::VideoMode::getFullscreenModes()[0].width / 2.5f), 
        (unsigned)(sf::VideoMode::getFullscreenModes()[0].height / 2.5f)
    );

    window.create(sf::VideoMode(size.x, size.y), title, sf::Style::Titlebar);
    window.setFramerateLimit(FPS_LIMIT);

    initInfo(font, info);
    initButtons(font);
}


bool InfoWindow::run()
{
    for (;;)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            okButton.get()->processEvent(event, sf::Mouse::getPosition(window));
            if (SHOW_CANCEL_BUTTON)
            {
                cancelButton.get()->processEvent(event, sf::Mouse::getPosition(window));
            }

            if (okButton.get()->isPressed())
            {
                window.close();
                return true;
            } 
            else if (SHOW_CANCEL_BUTTON && cancelButton->isPressed())
            {
                window.close();
                return false;
            }
        }

        window.clear(sf::Color::White);

        render();
        
        window.display();
    }
}


void InfoWindow::render()
{
    window.draw(info);
    okButton.get()->render(window);
    if (SHOW_CANCEL_BUTTON)
    {
        cancelButton.get()->render(window);
    }

}


void InfoWindow::initInfo(const sf::Font& font, const std::string& info)
{
    this->info.setFont(font);
    this->info.setColor(sf::Color::Black);
    this->info.setString(info);
    this->info.setCharacterSize((unsigned)utils::percentToPixels(3.f, (int)(window.getSize().x + window.getSize().y)));
    this->info.setPosition(
        std::floor(utils::percentToPixels(1.f, (int)window.getSize().x)),
        std::floor(utils::percentToPixels(14.5f, (int)window.getSize().y))
    );
}


void InfoWindow::initButtons(const sf::Font& font)
{
    const sf::Vector2f buttonSize((float)(window.getSize().x / 4u), (float)(window.getSize().y / 5u));
    sf::Vector2f okButtonPos(0.f, (float)(window.getSize().y - buttonSize.y * 1.5));
    sf::Vector2f cancelButtonPos;

    if (!SHOW_CANCEL_BUTTON)
    {
        okButtonPos.x = window.getSize().x / 2 - buttonSize.x / 2;
    }
    else
    {
        okButtonPos.x = utils::percentToPixels(10.f, (int)window.getSize().x);
        cancelButtonPos.x = window.getSize().x - buttonSize.x - utils::percentToPixels(10.f, (int)window.getSize().x);
        cancelButtonPos.y = okButtonPos.y;
    }


    okButton.reset(
        new Button(
                okButtonPos.x,
                okButtonPos.y,
                buttonSize.x,
                buttonSize.y,
                font,
                "OK",
                sf::Color::Black,
                sf::Color::Black,
                sf::Color::Black,
                sf::Color(130, 130, 130, 160),
                sf::Color(180, 180, 180, 200),
                sf::Color(220, 220, 220, 255),
                sf::Color(40, 40, 40, 255),
                sf::Color(80, 80, 80, 255),
                sf::Color(120, 120, 120, 255)
        )
    );  

    if (SHOW_CANCEL_BUTTON)
    {
        cancelButton.reset(
            new Button(
                    cancelButtonPos.x,
                    cancelButtonPos.y,
                    buttonSize.x,
                    buttonSize.y,
                    font,
                    "CANCEL",
                    sf::Color::Black,
                    sf::Color::Black,
                    sf::Color::Black,
                    sf::Color(130, 130, 130, 160),
                    sf::Color(180, 180, 180, 200),
                    sf::Color(220, 220, 220, 255),
                    sf::Color(40, 40, 40, 255),
                    sf::Color(50, 50, 50, 255),
                    sf::Color(60, 60, 60, 255)
            )
        );  
    }
}