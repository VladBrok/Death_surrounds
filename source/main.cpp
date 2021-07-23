#include "precompiled.h"
#include "Game.h"

/**
    TODO:
    - rename QUIT and CLOSE_STATE keybinds to something more specialized;
    - rename processEventS to processEvent;
    - in State, create enum with state types and make it required to specify the type in the constructor;
 */
 
 
int main()
{
	Game game;
    game.run();
    
	return 0;
}