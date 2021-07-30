#include "precompiled.h"
#include "Game.h"

/**
    TODO:
    - FIX stripes at the screen while moving the camera! (render the map on the texture first and then render only that texture!!!!!!!)
    - make the file names constant values and put them into "constants.h"
    - create a "ProgressBar" or "Bar" class and use it in PlayerGUI
 */
 
 
int main()
{
	Game game;
    game.run();
    
	return 0;
}