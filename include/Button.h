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


class Button: sf::NonCopyable
{
public:

                        Button(const float posX, const float posY, 
                               const float width, const float height,
                               sf::Font& font, 
                               const std::string& msg,

                               const sf::Color& textIdleColor, 
                               const sf::Color& textHoverColor, 
                               const sf::Color& textActiveColor,

                               const sf::Color& idleColor   = sf::Color::Transparent, 
                               const sf::Color& hoverColor  = sf::Color::Transparent,
                               const sf::Color& activeColor = sf::Color::Transparent
                               );
    void                update(const sf::Vector2f& mousePosition);
    void                render(sf::RenderTarget& target);
    bool                isPressed() const;

private:

    ButtonState         buttonState;
    sf::RectangleShape  shape;
    sf::Font&           font;
    sf::Text            text;
     
    // Button colors 
    sf::Color           idleColor;
    sf::Color           hoverColor;
    sf::Color           activeColor;
      
    // Text colors
    sf::Color           textIdleColor;
    sf::Color           textHoverColor;
    sf::Color           textActiveColor;

};


#endif // BUTTON_H
