#include "precompiled.h"
#include "ProgressBar.h"
#include "Utils.h"


ProgressBar::ProgressBar()
{
}


void ProgressBar::create(const float posX, 
                         const float posY, 
                         const float width, 
                         const float height,
                         const sf::Texture& barInnerTexture,
                         const sf::Color& backColor
                         )
{
    barBack.setSize(sf::Vector2f(width, height));
    barBack.setPosition(posX, posY);
    barBack.setFillColor(backColor);

    barInnerSprite.setTexture(barInnerTexture);
    barInnerSprite.setPosition(posX, posY);
}


void ProgressBar::update(const int value, const int valueMax)
{
    // Ratio of the value and the max value
    float ratio = static_cast<float>(value) / static_cast<float>(valueMax);

    // Updating the width of the inner bar using the ratio
    barInnerSprite.setTextureRect(
        sf::IntRect(0, 0, (int)(barBack.getSize().x * ratio), (int)barInnerSprite.getGlobalBounds().height)
    );
}


void ProgressBar::render(sf::RenderTarget& target)
{
    target.draw(barBack);
    target.draw(barInnerSprite);
}


 const sf::Vector2f& ProgressBar::getPosition() const
 {
     return barBack.getPosition();
 }


 const sf::Vector2f& ProgressBar::getBackSize() const
 {
     return barBack.getSize();
 }
