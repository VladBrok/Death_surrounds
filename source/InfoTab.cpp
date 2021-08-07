#include "precompiled.h"
#include "InfoTab.h"


InfoTab::InfoTab()
    : hidden(true)
{
}


void InfoTab::render(sf::RenderTarget& target)
{
    if (!hidden)
    {
        target.draw(tabBackground);
        target.draw(tabText);
    }
}


void InfoTab::hide()
{
    hidden = true;
}


void InfoTab::show()
{
    hidden = false;
}


bool InfoTab::isHidden() const
{
    return hidden;
}


void InfoTab::toggle()
{
    hidden = !hidden;
}