#include "precompiled.h"
#include "TextureSelector.h"
#include "constants.h"


TextureSelector::TextureSelector(const float posX, 
                                 const float posY, 
                                 const float width, 
                                 const float height,
                                 const sf::Texture& textureSheet
                                 )
    : textureSheet(textureSheet), active(false)
{
    bounds.setSize(sf::Vector2f(width, height));
    bounds.setPosition(posX, posY);
    bounds.setFillColor(sf::Color(50, 50, 50, 100));
    bounds.setOutlineColor(sf::Color::White);
    bounds.setOutlineThickness(1.f);

    sheet.setTexture(textureSheet);
    sheet.setPosition(posX, posY);

    textureRect.width = textureRect.height = static_cast<int>(GRID_SIZE);

    selector.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
    selector.setPosition(posX, posY);
    selector.setFillColor(sf::Color::Transparent);
    selector.setOutlineColor(sf::Color::Red);
    selector.setOutlineThickness(1.f);
}


void TextureSelector::processEvent(const sf::Event& event, const sf::Vector2i& mousePosWindow)
{
    /* Updating the activity status of the texture selector */
    if (event.type == sf::Event::MouseMoved)
    {
        active = bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow));

        if (active)
        {
            selector.setPosition(
                (int)(mousePosWindow.x - bounds.getPosition().x) / 
                (int)GRID_SIZE * GRID_SIZE + bounds.getPosition().x,

                (int)(mousePosWindow.y - bounds.getPosition().y) / 
                (int)GRID_SIZE * GRID_SIZE + bounds.getPosition().y
            );
        }
    }

    /* Selecting a new texture */
    else if (active && 
             event.type == sf::Event::MouseButtonPressed &&
             event.mouseButton.button == sf::Mouse::Left &&
             selector.getPosition().x - bounds.getPosition().x <= textureSheet.getSize().x - GRID_SIZE &&
             selector.getPosition().y - bounds.getPosition().y <= textureSheet.getSize().y - GRID_SIZE)
    {
        textureRect.left = (int)(selector.getPosition().x - bounds.getPosition().x);
        textureRect.top  = (int)(selector.getPosition().y - bounds.getPosition().y);
    }
}


void TextureSelector::render(sf::RenderTarget& target)
{
    target.draw(bounds);
    target.draw(sheet);

    if (active)
    {
        target.draw(selector);
    }
}


bool TextureSelector::isActive() const
{
    return active;
}


void TextureSelector::endActivity()
{
    active = false;
}


const sf::IntRect& TextureSelector::getTextureRect() const
{
    return textureRect;
}