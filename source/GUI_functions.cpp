#include "precompiled.h"
#include "GUI_functions.h"


namespace gui
{
    float percentToPixels(const float percent, const int size)
    {
        return size * (percent / 100.f);
    }
}