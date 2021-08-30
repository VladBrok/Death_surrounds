#include "precompiled.h"
#include "Game.h"
#include "ErrorWindow.h"


int main()
{
    try
    {
        try
        {
            Game game;
            game.run();
        }
        catch (std::bad_alloc&)
        {
            std::string msg("There is not enough RAM for the game to work.\n\
                             Please, close unnesessary programs and restart the game.");
            ErrorWindow erWindow(msg, false);
            erWindow.run();
        }
        catch (const std::exception& err)
        {
            std::cout << err.what() << '\n';

            throw; // Forwarding the error to an outer 'catch' block
        }
    }
    catch (...)
    {
        ErrorWindow erWindow("Fatal error. Please, try to reinstall the game.", false);
        erWindow.run();
    }
  
    return 0;
}