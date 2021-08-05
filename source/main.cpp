#include "precompiled.h"
#include "Game.h"

/**
    TODO:
    - FIX stripes at the screen while moving the camera! (render the map on the texture first and then render only that texture!!!!!!!)
    - create a "file paths" .cpp and .h with function like "getPathToPlayerTexture"
 */
 
 
int main()
{
    Game game;
    game.run();
  
    return 0;
}