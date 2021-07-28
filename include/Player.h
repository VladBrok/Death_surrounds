#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"


class Player: public Entity
{
public:
    
                    Player(const float posX, const float posY, sf::Texture& textureSheet);
    virtual         ~Player();
    virtual void    update(const float deltaTime);

    int             getHP() const;
    int             getHPMax() const;

    void            loseHP(const unsigned points);
    void            gainHP(const unsigned points);

private:

    bool            isAttacking;

    void            updateAttack();
    void            updateAnimation(const float deltaTime);
};


#endif // PLAYER_H
