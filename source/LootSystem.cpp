#include "precompiled.h"
#include "LootSystem.h"
#include "constants.h"


LootSystem::LootSystem(const sf::Texture& lootTextureSheet)
    : lootSprite(lootTextureSheet), 
      eliminationTimerMax(120.f)
{
}


void LootSystem::update(Player& player)
{
    auto bounty = loot.begin();
    while (bounty != loot.end())
    {
        bool intersectsWithPlayer = 
                player.getGlobalBounds().intersects((bounty->item)->getGlobalBounds()) &&
                player.getNumberOfItems() < INVENTORY_SIZE_MAX;

        if (intersectsWithPlayer)
        {
            player.addItemToInventory(bounty->item.get());
        }
        if (intersectsWithPlayer ||
            bounty->eliminationTimer.getElapsedTime().asSeconds() >= eliminationTimerMax)
        {
            bounty = loot.erase(bounty);
        }
        else
        {
            ++bounty;
        }
    }
}


void LootSystem::render(sf::RenderTarget& target)
{
    for (auto bounty = loot.begin(); bounty != loot.end(); ++bounty)
    {
        (bounty->item)->render(target);
    }
}


void LootSystem::addLoot(const float posX, const float posY, Item* pLoot)
{
    assert(pLoot);

    loot.push_back(Bounty(pLoot->getClone().release(), sf::Clock()));

    loot.back().item->setPosition(posX, posY);
}