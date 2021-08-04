#include "precompiled.h"
#include "Inventory.h"
#include "Item.h"


Inventory::Inventory(const int maxNumberOfItems)
    : maxNumberOfItems(maxNumberOfItems)
{
    assert(maxNumberOfItems > 0);
}


Inventory::~Inventory()
{
    clear();
}


void Inventory::update(const sf::Vector2f& itemPosition, const sf::Vector2f& mousePosView)
{
    for (auto i = items.begin(); i != items.end(); ++i)
    {
        (*i)->update(itemPosition, mousePosView);
    }
}


void Inventory::render(sf::RenderTarget& target)
{
    for (auto i = items.begin(); i != items.end(); ++i)
    {
        (*i)->render(target);
    }
}


void Inventory::saveToFile(const std::string& fileName)
{
}


void Inventory::loadFromFile(const std::string& fileName)
{
}


bool Inventory::addItem(Item* item)
{
    if ((int)items.size() < maxNumberOfItems)
    {
        items.push_back(item->getClone());
        return true;
    }
    return false;
}


void Inventory::removeItem(const int index)
{
    assert(index >= 0 && index < (int)items.size());

    auto toRemove = items.begin();
    std::advance(toRemove, index);
    delete *toRemove;
    items.erase(toRemove);
}


bool Inventory::isEmpty() const
{
    return items.empty();
}


int Inventory::getSize() const
{
    return (int)items.size();
}


Item& Inventory::operator[](const int index)
{
    assert(index >= 0 && index < (int)items.size());

    auto it = items.begin();
    std::advance(it, index);

    return **it;
}


void Inventory::clear()
{
    for (auto i = items.begin(); i != items.end(); ++i)
    {
        delete *i;
    }
    items.clear();
}

