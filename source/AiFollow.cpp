#include "precompiled.h"
#include "AiFollow.h"
#include "Utils.h"


AiFollow::AiFollow(Entity& self, Entity& targetEntity)
    : self(self), targetEntity(targetEntity)
{
}


void AiFollow::update(const float deltaTime)
{
    if (static_cast<sf::Vector2i>(self.getCenter()) != static_cast<sf::Vector2i>(targetEntity.getCenter()))
    {
        sf::Vector2f movementDirection(
            utils::getNormalizedDirection(
                self.getCenter(), 
                targetEntity.getCenter()
            )
        );

        self.move(movementDirection.x, movementDirection.y, deltaTime);
    }
    else
    {
        self.stopVelocity();
    }
}