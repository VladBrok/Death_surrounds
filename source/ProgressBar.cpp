#include "precompiled.h"
#include "ProgressBar.h"
#include "GUI_functions.h"


ProgressBar::ProgressBar()
{
}


void ProgressBar::create(const float posX, 
                         const float posY, 
                         const float width, 
                         const float height,
                         sf::Font& font,
                         const sf::Color& innerColor,
                         const sf::Color& backColor,
                         const bool centerText,
                         const std::string& barTextStr
                         )
{
    barBack.setSize(sf::Vector2f(width, height));
    barBack.setPosition(posX, posY);
    barBack.setFillColor(backColor);

    barInner.setSize(sf::Vector2f(width, height));
    barInner.setPosition(posX, posY);
    barInner.setFillColor(innerColor);

    barText.setFont(font);
    barText.setString(barTextStr);
    barText.setCharacterSize((unsigned)(height / 2.5f));

    if (!centerText)
    {
        barText.setPosition(
            std::floor(posX + gui::percentToPixels(5.f, width)), 
            std::floor(posY + height / 4.f)
        );
    }
    else
    {
        barText.setPosition(
            std::floor(posX + width / 2.0f - barText.getGlobalBounds().width / 3.f),
            std::floor(posY + height / 2.f - barText.getGlobalBounds().height / 1.5f)
        );
    }
}


void ProgressBar::update(const int value, const int valueMax)
{
    // Ratio of the value and the max value
    float ratio = static_cast<float>(value) / static_cast<float>(valueMax);

    // Updating the width of the inner bar using the ratio
    barInner.setSize(
        sf::Vector2f(
            barBack.getSize().x * ratio, 
            barInner.getSize().y
        )
    );

    barText.setString(
        std::to_string((long long)value) + " / " + 
        std::to_string((long long)valueMax)
    );
}


void ProgressBar::render(sf::RenderTarget& target)
{
    target.draw(barBack);
    target.draw(barInner);
    target.draw(barText);
}


 const sf::Vector2f& ProgressBar::getPosition() const
 {
     return barBack.getPosition();
 }


 const sf::Vector2f& ProgressBar::getBackSize() const
 {
     return barBack.getSize();
 }


void ProgressBar::setTextString(const std::string& string)
{
    barText.setString(string);
}