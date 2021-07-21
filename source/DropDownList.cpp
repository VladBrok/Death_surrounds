#include "DropDownList.h"
#include <cassert>


DropDownList::DropDownList(const float posX,
                           const float posY,
                           const float elementWidth,
                           const float elementHeight,
                           sf::Font& font,
                           const std::vector<std::string>& list,
                           const int activeElementIndex
                           )
    : font(font), showList(false), hoveredElementIndex(-1)
{
    assert(activeElementIndex >= 0 && activeElementIndex < (int)list.size());

    for (int i = 0; i < (int)list.size(); ++i)
    {
        if (i == 0) // Creating active list element
        {
           listElements.push_back(
                new Button(
                    posX, posY + elementHeight * i,
                    elementWidth, elementHeight,
                    font, 
                    list[i],
                    sf::Color::White,
                    sf::Color::White,
                    sf::Color::White,
                    sf::Color(70, 70, 70, 200),
                    sf::Color(40, 40, 40, 200),
                    sf::Color(40, 40, 40, 200),
                    sf::Color(200, 200, 200, 200),
                    sf::Color(220, 220, 220, 230),
                    sf::Color::White
                )
            );
        }
        else // Creating regular list element
        {
            listElements.push_back(
                new Button(
                    posX, posY + elementHeight * i,
                    elementWidth, elementHeight,
                    font, 
                    list[i],
                    sf::Color::White,
                    sf::Color::White,
                    sf::Color::White,
                    sf::Color(100, 100, 100, 180),
                    sf::Color(150, 150, 150, 200),
                    sf::Color(40, 40, 40, 200)
                )
            ); 
        }

    }

    if (activeElementIndex != 0)
    {
        swapListElementTexts(0, activeElementIndex);
    }
}


DropDownList::~DropDownList()
{
    for (auto e = listElements.begin(); e != listElements.end(); ++e)
    {
        delete *e;
    }
}


void DropDownList::processMouseEvent(const sf::Event& event,
                                     const sf::Vector2f& mousePosition
                                     )
{
    if (!showList)
    {
        listElements[0]->processMouseEvent(event, mousePosition);

        if (listElements[0]->isPressed())
        {
            showList = true;
        }
    }
    else if (hoveredElementIndex == -1)
    {
        for (int i = 0; (i < (int)listElements.size()) && hoveredElementIndex == -1 && showList; ++i)
        {
            listElements[i]->processMouseEvent(event, mousePosition);

            if (listElements[i]->isHovered())
            {
                hoveredElementIndex = i;
            }
            else if (listElements[i]->isPressed())
            {
                showList = false;
                if (i != 0)
                {
                    swapListElementTexts(0, i);
                }
            }
        }
    }
    else
    {
        listElements[hoveredElementIndex]->processMouseEvent(event, mousePosition);

        if (listElements[hoveredElementIndex]->isPressed())
        {
            showList = false;
            if (hoveredElementIndex != 0)
            {
                swapListElementTexts(0, hoveredElementIndex);
                hoveredElementIndex = -1;
            }
        }

        else if (!listElements[hoveredElementIndex]->isHovered())
        {
            hoveredElementIndex = -1;
        }
    }
}


void DropDownList::render(sf::RenderTarget& target)
{
    listElements[0]->render(target);

    if (showList)
    {
        for (int i = 1; i < (int)listElements.size(); ++i)
        {
            listElements[i]->render(target);
        }
    }
}


const std::string& DropDownList::getActiveElementText() const
{
    return listElements[0]->getText();
}


void DropDownList::swapListElementTexts(const int element1_index, const int element2_index)
{
    std::string tmp = listElements[element1_index]->getText();
    listElements[element1_index]->setText(listElements[element2_index]->getText());
    listElements[element2_index]->setText(tmp);
}