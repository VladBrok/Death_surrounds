#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Sword.h"
#include "Inventory.h"


class Player: public Entity
{
public:
    
                    Player(const float posX, const float posY, sf::Texture& textureSheet, Inventory& inventory);
    virtual void    update(const float deltaTime, const sf::Vector2f& mousePosView);
    virtual void    render(sf::RenderTarget& target, 
                           sf::Shader* pShader = nullptr,
                           const sf::Vector2f& shaderLightPosition = sf::Vector2f(),
                           const bool showHitbox = false
                           );

    int             getHP() const;
    int             getHPMax() const;
    int             getExp() const;
    int             getExpForNextLevel() const;
    unsigned        getLevel() const;

    void            loseHp(const unsigned hp);
    void            gainHp(const unsigned hp);
    void            loseExp(const unsigned exp);
    void            gainExp(const unsigned exp);

private:

    Inventory&      inventory;

    void            updateAnimation(const float deltaTime);
    void            updateInventory(const sf::Vector2f& mousePosView);
    void            renderInventory(sf::RenderTarget& target);
};


#endif // PLAYER_H
