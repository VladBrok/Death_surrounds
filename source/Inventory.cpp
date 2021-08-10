#include "precompiled.h"
#include "Inventory.h"
#include "Item.h"


Inventory::Inventory(const int maxNumberOfItems)
    : maxNumberOfItems(maxNumberOfItems), pActiveItem(nullptr)
{
    assert(maxNumberOfItems > 0);
}


Inventory::~Inventory()
{
    clear();
}


void Inventory::update(const sf::Vector2f& itemPosition, const sf::Vector2f& mousePosView)
{
    pActiveItem->update(itemPosition, mousePosView);

    //for (auto i = items.begin(); i != items.end(); ++i)
    //{
    //    (*i)->update(itemPosition, mousePosView);
    //}
}


void Inventory::render(sf::RenderTarget& target)
{
    pActiveItem->render(target);

    //for (auto i = items.begin(); i != items.end(); ++i)
    //{
    //    (*i)->render(target);
    //}
}


bool Inventory::addItem(Item* pItem)
{
    assert(pItem != nullptr);

    if ((int)items.size() < maxNumberOfItems)
    {
        items.push_back(pItem->getClone());
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


void Inventory::setActiveItem(const int index)
{
    assert(index >= 0 && index < (int)items.size());

    pActiveItem = &this->operator[](index);
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


Item& Inventory::back()
{
    if (items.empty())
    {
        throw std::runtime_error("ERROR in Inventory::back: vector of items is empty\n");
    }
    return *items.back();
}


void Inventory::clear()
{
    for (auto i = items.begin(); i != items.end(); ++i)
    {
        delete *i;
    }
    items.clear();
}

