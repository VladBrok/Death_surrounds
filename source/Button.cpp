#include "precompiled.h"
#include "Button.h"


Button::Button(const float posX, const float posY, 
               const float width, const float height,
               sf::Font& font, 
               const std::string& text, 

               const sf::Color& textIdleColor, 
               const sf::Color& textHoverColor, 
               const sf::Color& textActiveColor,

               const sf::Color& idleColor, 
               const sf::Color& hoverColor,
               const sf::Color& activeColor,

               const sf::Color& outlineIdleColor,
               const sf::Color& outlineHoverColor,   
               const sf::Color& outlineActiveColor
               )

    : buttonState        (BTN_IDLE),
      font               (font),
      text               (text),
      idleColor          (idleColor), 
      hoverColor         (hoverColor),
      activeColor        (activeColor),
      textIdleColor      (textIdleColor),
      textHoverColor     (textHoverColor),
      textActiveColor    (textActiveColor),
      outlineIdleColor   (outlineIdleColor),
      outlineHoverColor  (outlineHoverColor),
      outlineActiveColor (outlineActiveColor)
      
{
    shape.setPosition(posX, posY);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(idleColor);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(outlineIdleColor);

    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(static_cast<unsigned>(shape.getSize().y / 1.55f));
    sfText.setColor(textIdleColor);
    sfText.setPosition(
        shape.getPosition().x + shape.getSize().x / 2.f - sfText.getGlobalBounds().width / 2.f,
        shape.getPosition().y + shape.getSize().y / 2.f - sfText.getGlobalBounds().height / 1.3f
    ); 
}


void Button::processEvent(const sf::Event& event, const sf::Vector2i& mousePosWindow)
{
    buttonState = BTN_IDLE;

    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) // Hover
    {
        buttonState = BTN_HOVER;
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)  // Left button of the mouse is pressed
        {
            buttonState = BTN_ACTIVE;
        }
    }
        
    // Changing the button appearance in accordance with the button state
    switch (buttonState)
    {
    case BTN_IDLE:
        shape.setFillColor(idleColor);
        shape.setOutlineColor(outlineIdleColor);
        sfText.setColor(textIdleColor);
        break;
    case BTN_HOVER:
        shape.setFillColor(hoverColor);
        shape.setOutlineColor(outlineHoverColor);
        sfText.setColor(textHoverColor);
        break;
    case BTN_ACTIVE:
        shape.setFillColor(activeColor);
        shape.setOutlineColor(outlineActiveColor);
        sfText.setColor(textActiveColor);
        break;
    default: // This should never happen
        shape.setFillColor(sf::Color::Red);
        shape.setOutlineColor(sf::Color::Green);
        sfText.setColor(sf::Color::Blue);
    }
}


void Button::render(sf::RenderTarget& target)
{
    target.draw(shape);
    target.draw(sfText);
}


bool Button::isPressed(const bool resetButtonStateToIdle)
{
    if (buttonState == BTN_ACTIVE && resetButtonStateToIdle)
    {
        buttonState = BTN_IDLE;
        shape.setFillColor(idleColor);
        shape.setOutlineColor(outlineIdleColor);
        sfText.setColor(textIdleColor);

        return true;
    }
    return buttonState == BTN_ACTIVE;
}


bool Button::isHovered() const
{
    return buttonState == BTN_HOVER;
}


void Button::setText(const std::string& newText)
{
    text = newText;

    sfText.setString(newText);

    sfText.setPosition(
        shape.getPosition().x + shape.getSize().x / 2.f - sfText.getGlobalBounds().width / 2.f,
        shape.getPosition().y + shape.getSize().y / 2.f - sfText.getGlobalBounds().height / 1.3f
    ); 
}


const std::string& Button::getText() const
{
    return text;
}
