#define NOMINMAX
#include <Windows.h>
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>  
#include <crtdbg.h>   //for malloc and free


#include "precompiled.h"
#include "Game.h"



/**
    TODO:
    - FIX stripes at the screen while moving the camera! (render the map on the texture first and then render only that texture!!!!!!!)
    - create a "file paths" .cpp and .h with function like "getPathToPlayerTexture"
 */
 
 
int main()
{
    _CrtMemState sOld;
    _CrtMemState sNew;
    _CrtMemState sDiff;
    _CrtMemCheckpoint(&sOld); //take a snapchot


    {
        Game game;
        game.run();
    }

    

    _CrtMemCheckpoint(&sNew); //take a snapchot 

    if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
    {

        //_CrtMemDumpStatistics(&sDiff);

        //_CrtMemDumpAllObjectsSince(&sOld);

        _CrtDumpMemoryLeaks();
    }

    
    return 0;
}