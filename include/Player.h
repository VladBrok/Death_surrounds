#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"


class Player: public Entity
{
public:
    
                    Player(const float posX, const float posY, sf::Texture& textureSheet);
    virtual         ~Player();
    virtual void    update(const float deltaTime);

private:
};


#endif // PLAYER_H
