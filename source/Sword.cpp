#include "precompiled.h"
#include "Sword.h"
#include "Utils.h"


Sword::Sword(const sf::Texture& texture, 
             const int damageMin, 
             const int damageMax,
             const sf::IntRect& textureRect
             )
    : Weapon(texture, damageMin, damageMax, textureRect)
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


std::unique_ptr<Item> Sword::getClone()
{
    std::unique_ptr<Sword> clone(new Sword(*this));
    return std::move(clone);
}


const std::string Sword::getName() const
{
    return "Soul slicer";
}


WeaponType Sword::getWeaponType() const
{
    return MELEE_WEAPON;
}


void Sword::initRange()
{
    range = 58.f;
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