#ifndef BUTTON_H
#define BUTTON_H


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
                               const std::string& text,

                               const sf::Color& textIdleColor, 
                               const sf::Color& textHoverColor, 
                               const sf::Color& textActiveColor,

                               const sf::Color& idleColor          = sf::Color::Transparent, 
                               const sf::Color& hoverColor         = sf::Color::Transparent,
                               const sf::Color& activeColor        = sf::Color::Transparent,

                               const sf::Color& outlineIdleColor   = sf::Color::Transparent, 
                               const sf::Color& outlineHoverColor  = sf::Color::Transparent, 
                               const sf::Color& outlineActiveColor = sf::Color::Transparent
                               );
    void                processMouseEvent(const sf::Event& event, const sf::Vector2f& mousePosition);
    void                render(sf::RenderTarget& target);
    bool                isPressed(const bool resetButtonStateToIdle = true);
    bool                isHovered() const;

    void                setText(const std::string& newText);
    const std::string&  getText() const;

private:

    ButtonState         buttonState;
    sf::RectangleShape  shape;
    sf::Font&           font;
    sf::Text            sfText;
    std::string         text;
     
    // Button colors 
    sf::Color           idleColor;
    sf::Color           hoverColor;
    sf::Color           activeColor;
      
    // Text colors
    sf::Color           textIdleColor;
    sf::Color           textHoverColor;
    sf::Color           textActiveColor;

    // Outline colors
    sf::Color           outlineIdleColor;
    sf::Color           outlineHoverColor;
    sf::Color           outlineActiveColor;
};


#endif // BUTTON_H
