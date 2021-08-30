#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include "Button.h"


class InfoWindow
{
public:

                              InfoWindow(const std::string& title,
                                         const std::string& info,
                                         const bool showCancelButton
                                         );
   virtual                    ~InfoWindow() {};
   // Returns true if the "OK" button was pressed, false if the "CANCEL" button was pressed
   bool                       run();

protected:                     
                               
   sf::RenderWindow           window;
   sf::Font                   font;
   sf::Text                   info;
   std::shared_ptr<Button>    okButton;
   std::shared_ptr<Button>    cancelButton;
   const bool                 SHOW_CANCEL_BUTTON;

   virtual void               render();

   void                       initInfo(const sf::Font& font, const std::string& info);
   void                       initButtons(const sf::Font& font);
};


#endif // WINDOW_H
