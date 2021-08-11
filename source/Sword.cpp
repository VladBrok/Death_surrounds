#include "precompiled.h"
#include "Sword.h"
#include "Utils.h"


Sword::Sword(const sf::Texture& texture, 
             const int damage, 
             const int damageMax,
             const sf::IntRect& textureRect
             )
    : Weapon(texture, damage, damageMax, textureRect)
{
    initRange();
    initAttackTimerMax();
    initDefaultOriginAndScale();

    sprite.setOrigin(defaultOrigin);
}


void Sword::update(const sf::Vector2f& weaponPosition, const sf::Vector2f& mousePosView)
{
    if (attackTimer.getElapsedTime().asMilliseconds() < attackTimerMax / 2)
    {
        sf::Vector2f swordPosOffset(utils::getNormalizedDirection(sprite.getPosition(), mousePosView));

        sprite.setPosition(
            weaponPosition.x + swordPosOffset.x * 10.f, 
            weaponPosition.y + swordPosOffset.y * 10.f
        );
    }
    else
    {
        sprite.setPosition(weaponPosition);

        utils::lookAt(sprite, mousePosView);
    }
}


Sword* Sword::getClone()
{
    return new Sword(*this);
}


void Sword::initRange()
{
    range = 55.f;
}


void Sword::initAttackTimerMax()
{
    attackTimerMax = 200;
}


void Sword::initDefaultOriginAndScale()
{
    defaultOrigin.x = sprite.getGlobalBounds().width / 2.f;
    defaultOrigin.y = sprite.getGlobalBounds().height;
    
    defaultScale.x = defaultScale.y = 1.f;
}