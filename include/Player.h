#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"


class Player: public Entity
{
public:
    
    Player(const float posX, const float posY, const sf::Texture& texture);
    virtual ~Player();

private:
};


#endif // PLAYER_H
