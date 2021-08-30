#ifndef LOOTSYSTEM_H
#define LOOTSYSTEM_H

#include "Player.h"
#include "Item.h"


class LootSystem
{
public:

    explicit             LootSystem(const sf::Texture& lootTextureSheet);
                         ~LootSystem();
    void                 update(Player& player);
    void                 render(sf::RenderTarget& target);

    // This function will place a copy of the item to the LootSystem
    void                 addLoot(const float posX, const float posY, Item* pLoot);

private:


    struct Bounty
    {
        Bounty(Item* pItem, sf::Clock eliminationTimer)
            : pItem(pItem), eliminationTimer(eliminationTimer)
        {
        }

        Item* pItem;
        sf::Clock eliminationTimer;
    };


    sf::Sprite           lootSprite;
    std::list<Bounty>    loot;
    float                eliminationTimerMax;

};


#endif // LOOTSYSTEM_H
