#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"


class Projectile: public Entity
{
public:

                 Projectile(const sf::Texture& texture,
                            const sf::Vector2f& position,
                            const sf::Vector2f& movementDir,
                            const float speed,
                            const float lifetimeInSeconds,
                            const int damageMin,
                            const int damageMax
                            );

    void         update(const float deltaTime);
    bool         checkIntersection(const Entity& entity);

    bool         canBeRemoved() const;
    int          getDamage() const;

private:

    sf::Clock    eliminationTimer;
    float        eliminationTimerMax;

    float        movementDirX;
    float        movementDirY;
    float        speed;
    int          damageMin;
    int          damageMax;
};


#endif // PROJECTILE_H
