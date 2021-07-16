#include "Button.h"


Button::Button(const float posX, const float posY, 
               const float width, const float height,
               sf::Font* font, 
               const std::string& msg, 

               const sf::Color& textIdleColor, 
               const sf::Color& textHoverColor, 
               const sf::Color& textActiveColor,

               const sf::Color& idleColor, 
               const sf::Color& hoverColor,
               const sf::Color& activeColor
               )

    : buttonState(BTN_IDLE),
      font(font),
      idleColor(idleColor), 
      hoverColor(hoverColor),
      activeColor(activeColor),
      textIdleColor(textIdleColor),
      textHoverColor(textHoverColor),
      textActiveColor(textActiveColor)
      
{
    shape.setPosition(posX, posY);
    shape.setSize(sf::Vector2f(width, height));

    text.setFont(*font);
    text.setString(msg);
    text.setCharacterSize(shape.getSize().x / 4);
    text.setColor(textIdleColor);
    text.setPosition(
        shape.getPosition().x + shape.getSize().x / 2.f - text.getGlobalBounds().width / 2.f,
        shape.getPosition().y + shape.getSize().y / 2.f - text.getGlobalBounds().height * 1.1f
        ); 
}


void Button::update(const sf::Vector2f& mousePosition)
{
    buttonState = BTN_IDLE;

    if (shape.getGlobalBounds().contains(mousePosition))
    {
        buttonState = BTN_HOVER;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            buttonState = BTN_ACTIVE;
        }
    }
    
    switch (buttonState)
    {
    case BTN_IDLE:
        shape.setFillColor(idleColor);
        text.setColor(textIdleColor);
        break;
    case BTN_HOVER:
        shape.setFillColor(hoverColor);
        text.setColor(textHoverColor);
        break;
    case BTN_ACTIVE:
        shape.setFillColor(activeColor);
        text.setColor(textActiveColor);
        break;
    default: // This should never happen
        shape.setFillColor(sf::Color::Red);
        text.setColor(sf::Color::Blue);
    }
}


void Button::render(sf::RenderTarget& target)
{
    target.draw(shape);
    target.draw(text);
}


const bool Button::isPressed() const
{
    return buttonState == BTN_ACTIVE;
}