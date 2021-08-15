#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include "InfoWindow.h"


class ErrorWindow: public InfoWindow
{
public:

                    ErrorWindow(const std::string& info,
                                const bool showCancelButton
                                );

private:

    sf::Text        errorText;

    virtual void    render();
};


#endif // ERRORWINDOW_H
