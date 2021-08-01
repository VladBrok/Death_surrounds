#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Sword.h"


class Player: public Entity
{
public:
    
                    Player(const float posX, const float posY, sf::Texture& textureSheet);
    virtual void    update(const float deltaTime, const sf::Vector2f& mousePosView);
    virtual void    render(sf::RenderTarget& target, 
                           sf::Shader* pShader   = nullptr,
                           const bool showHitbox = false
                           );

    int             getHP() const;
    int             getHPMax() const;
    int             getExp() const;
    int             getExpForNextLevel() const;
    unsigned        getLevel() const;

    void            loseHP(const unsigned points);
    void            gainHP(const unsigned points);
    void            loseExp(const unsigned exp);
    void            gainExp(const unsigned exp);

private:

    Sword           sword;
    bool            isAttacking; // FIXME: Current player don't have the attack animation

    void            updateAttack(); // FIXME
    void            updateAnimation(const float deltaTime);
};


#endif // PLAYER_H
