#include "precompiled.h"
#include "Projectile.h"


Projectile::Projectile(const sf::Texture& texture, 
                       const sf::Vector2f& position,
                       const sf::Vector2f& movementDir,
                       const float speed,
                       const float lifetimeInSeconds,
                       const int damageMin,
                       const int damageMax
                       )
    : Entity(texture),
      movementDirX(movementDir.x),
      movementDirY(movementDir.y),
      eliminationTimerMax(lifetimeInSeconds),
      damageMin(damageMin),
      damageMax(damageMax),
      speed(speed)
{
    sprite.setOrigin((float)(texture.getSize().x / 2u), (float)(texture.getSize().y / 2u));
    sprite.setPosition(position.x, position.y);
}


void Projectile::update(const float deltaTime)
{
    sprite.move(movementDirX * deltaTime * speed, movementDirY * speed * deltaTime);
}


bool Projectile::checkIntersection(const Entity& entity)
{
    return entity.getGlobalBounds().intersects(this->getGlobalBounds());
}


bool Projectile::canBeRemoved() const
{
    return eliminationTimer.getElapsedTime().asSeconds() >= eliminationTimerMax;
}


int Projectile::getDamage() const
{
    return rand() % (damageMax - damageMin + 1) + damageMin;
}