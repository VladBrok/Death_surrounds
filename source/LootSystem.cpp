#include "precompiled.h"
#include "LootSystem.h"
#include "constants.h"


LootSystem::LootSystem(const sf::Texture& lootTextureSheet)
    : lootSprite(lootTextureSheet), eliminationTimerMax(120.f)
{
}


LootSystem::~LootSystem()
{
    for (auto bounty = loot.begin(); bounty != loot.end(); ++bounty)
    {
        delete bounty->pItem;
    }
}


void LootSystem::update(Player& player)
{
    auto bounty = loot.begin();
    while (bounty != loot.end())
    {
        bool intersectsWithPlayer = 
                player.getGlobalBounds().intersects((bounty->pItem)->getGlobalBounds()) &&
                player.getNumberOfItems() < INVENTORY_SIZE_MAX;

        if (intersectsWithPlayer)
        {
            player.addItemToInventory(bounty->pItem);
        }
        if (intersectsWithPlayer || bounty->eliminationTimer.getElapsedTime().asSeconds() >= eliminationTimerMax)
        {
            delete bounty->pItem;
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
        (bounty->pItem)->render(target);
    }
}


void LootSystem::addLoot(const float posX, const float posY, Item* pLoot)
{
    assert(pLoot != nullptr);

    loot.push_back(Bounty(pLoot->getClone(), sf::Clock()));

    loot.back().pItem->setPosition(posX, posY);
}