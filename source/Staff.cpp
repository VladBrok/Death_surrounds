#include "precompiled.h"
#include "Staff.h"
#include "Utils.h"
#include "Projectile.h"


Staff::Staff(const sf::Texture& texture, 
             const sf::Texture& projectileTexture,
             const int projectileDamageMin, 
             const int projectileDamageMax,
             const sf::IntRect& textureRect
             )
    : RangedWeapon(texture, projectileTexture, projectileDamageMin, projectileDamageMax, textureRect),
      projectileTexture(projectileTexture)
{
    initRange();
    initAttackTimerMax();
    initDefaultOriginAndScale();

    sprite.setOrigin(defaultOrigin);


    projectileLifetimeInSeconds = 5.f;
    projectileSpeed             = 300.f;
}


void Staff::update(const sf::Vector2f& weaponPosition, const sf::Vector2f& mousePosView)
{
    if (attackTimer.getElapsedTime().asMilliseconds() < attackTimerMax / 2)
    {
        sf::Vector2f StaffPosOffset(utils::getNormalizedDirection(sprite.getPosition(), mousePosView));

        sprite.setPosition(
            weaponPosition.x + StaffPosOffset.x * 10.f, 
            weaponPosition.y + StaffPosOffset.y * 10.f
        );
    }
    else
    {
        sprite.setPosition(weaponPosition);

        utils::lookAt(sprite, mousePosView);
    }
}


Staff* Staff::getClone()
{
    return new Staff(*this);
}


const std::string Staff::getName() const
{
    return "Warlock's staff";
}


void Staff::initRange()
{
    range = 200.f;
}


void Staff::initAttackTimerMax()
{
    attackTimerMax = 1500;
}


void Staff::initDefaultOriginAndScale()
{
    defaultOrigin.x = sprite.getGlobalBounds().width / 2.f;
    defaultOrigin.y = sprite.getGlobalBounds().height;
    
    defaultScale.x = defaultScale.y = 1.f;
}


Projectile* Staff::allocateNewProjectile(const sf::Vector2f& movementDir, const sf::Vector2f& position)
{
    return new Projectile(projectileTexture, position, movementDir, projectileSpeed, projectileLifetimeInSeconds, damageMin, damageMax);
}