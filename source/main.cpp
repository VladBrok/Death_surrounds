#include "precompiled.h"
#include "Game.h"
#include "ErrorWindow.h"

/* 
    TODO:
        - add a companion (bird or dog);
        - i don't like that many classes have a reference to the player!!!;
*/


int main()
{
    try
    {
        try
        {
            Game game;
            game.run();
        }
        catch (const std::bad_alloc& err)
        {
            ErrorWindow erWindow(
                           "There is not enough RAM for the game to work.\nPlease, close unnesessary programs and restart the game.",
                           false
                        );
            erWindow.run();
        }
        catch (const std::exception& err)
        {
            std::cout << err.what() << '\n';

            throw;
        }
    }
    catch (...)
    {
        ErrorWindow erWindow(
                        "Fatal error. Please, try to reinstall the game.",
                         false
                    );
        erWindow.run();
    }
  
    return 0;
}