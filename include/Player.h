#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Inventory.h"
#include "Weapon.h"


class Player: public Character
{
public:
    
                         Player(const float posX, 
                                const float posY, 
                                const sf::Texture& textureSheet,
                                const sf::Texture& inventoryPanelTexture,
                                const sf::RenderWindow& window
                                );
    virtual void         update(const float deltaTime, 
                                const sf::Vector2f& mousePosView,
                                const sf::Vector2i& mousePosWindow,
                                TextTagSystem& textTagSystem
                                );
    virtual void         render(sf::RenderTarget& target, 
                                sf::Shader* pShader = nullptr,
                                const sf::Vector2f& shaderLightPosition = sf::Vector2f(),
                                const bool showHitbox = false
                                );

    bool                 addItemToInventory(Item*, const bool setAsActive = false);
    void                 removeActiveItem();
    Item*                getActiveItem() const;
                         
    int                  getHp() const;
    int                  getHpMax() const;

    int                  getExp() const;
    int                  getExpForNextLevel() const;

    unsigned             getLevel() const;
    virtual int          getDamage() const;
    float                getAttackRange() const;
    const std::string    getStatsAsString() const;
    int                  getNumberOfItems() const;
    WeaponType           getActiveWeaponType() const;

    void                 loseExp(const int exp);
    void                 gainExp(const int exp);
                         
    void                 setAttackStatus(const bool attacking);
    bool                 isAttacking() const;
    virtual bool         canAttack() const;
    bool                 deathAnimationIsDone() const;

    // Shows the inventory panel if it's hidden and vise versa
    void                 toggleInventoryPanel();
                         
private:                 
                         
    Inventory            inventory;
    Weapon*              pActiveWeapon;
    bool                 attacking;
    bool                 deathAnimationDone;
           
    virtual void         initTimers();
};


#endif // PLAYER_H
