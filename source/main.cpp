#include "precompiled.h"
#include "Game.h"

/* 
    Typedef examples:
        typedef std::map<std::string, int> StringToIntMap;
        typedef std::list<int> IntList;

    TODO:
        - i don't like that many classes have a reference to the player!!!
        - remove idle animations
        - MOVE updateAnimation method to character base class !!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

//---------------------------
// typedef std::unordered_map<std::string, sf::Keyboard::Key> StringToKeyMap;
// StringToKeyMap map;
//----------------------------
 
int main()
{
    Game game;
    game.run();
  
    return 0;
}