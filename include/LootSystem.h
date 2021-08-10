#ifndef LOOTSYSTEM_H
#define LOOTSYSTEM_H

#include "Player.h"
#include "Item.h"


class LootSystem
{
public:

                        LootSystem(const sf::Texture& lootTextureSheet);
                        ~LootSystem();
    void                update(Player& player);
    void                render(sf::RenderTarget& target);

    // This function will place a copy of the item to the LootSystem
    void                addLoot(const float posX, const float posY, Item* pLoot);

private:

    sf::Sprite          lootSprite;
    std::list<Item*>    loot;
};


#endif // LOOTSYSTEM_H
