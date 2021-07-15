#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"


class Entity
{
public:

                        Entity();
    virtual             ~Entity();
    void                createSprite(sf::Texture* const texture);
    void                createMovementComponent(const float maxVelocity);
    void                setPosition(const float posX, const float posY);
    virtual void        update(const float deltaTime) = 0;
    virtual void        render(sf::RenderTarget* target);
    virtual void        move(const float dirX, const float dirY, const float deltaTime);

protected:

    sf::Texture*        pTexture;
    sf::Sprite*         pSprite;
    MovementComponent*  pMovementComponent; // We won't be able to move entity if this equals nullptr

};


#endif // ENTITY_H
