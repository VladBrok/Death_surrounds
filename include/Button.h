#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>


enum ButtonState
{
    BTN_IDLE,
    BTN_HOVER,
    BTN_ACTIVE
};


class Button
{
public:

    Button(const float posX, const float posY, const float width, const float height,
           sf::Font* font, const std::string& msg, 
           const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor
           );
    void update(const sf::Vector2f& mousePosition);
    void render(sf::RenderTarget& target);
    const bool isPressed() const;

private:

    ButtonState buttonState;
    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

};


#endif // BUTTON_H
