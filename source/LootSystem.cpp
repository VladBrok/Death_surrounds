#include "precompiled.h"
#include "LootSystem.h"
#include "constants.h"


LootSystem::LootSystem(const sf::Texture& lootTextureSheet)
    : lootSprite(lootTextureSheet)
{
}


LootSystem::~LootSystem()
{
    for (auto l = loot.begin(); l != loot.end(); ++l)
    {
        delete *l;
    }
}


void LootSystem::update(Player& player)
{
    if (player.getNumberOfItems() >= INVENTORY_SIZE_MAX)
    {
        return;
    }

    auto l = loot.begin();
    while (l != loot.end())
    {
        if (player.getGlobalBounds().intersects((*l)->getGlobalBounds()))
        {
            player.addItemToInventory(*l);
            delete *l;
            l = loot.erase(l);
        }
        else
        {
            ++l;
        }
    }
}


void LootSystem::render(sf::RenderTarget& target)
{
    for (auto l = loot.begin(); l != loot.end(); ++l)
    {
        (*l)->render(target);
    }
}


void LootSystem::addLoot(const float posX, const float posY, Item* pLoot)
{
    assert(pLoot != nullptr);

    pLoot->setPosition(posX, posY);

    loot.push_back(pLoot->getClone());
}