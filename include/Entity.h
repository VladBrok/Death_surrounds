#ifndef ENTITY_H
#define ENTITY_H

#include "SFML/Graphics.hpp"


class Entity
{
public:

    Entity();
    virtual ~Entity();
    virtual void update();
    virtual void render(sf::RenderTarget* target);
    virtual void move(const float dirX, const float dirY, const float deltaTime);

protected:

    float movementSpeed;
    sf::RectangleShape entityShape;

};


#endif // ENTITY_H
