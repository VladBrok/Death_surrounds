#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"


class Game: public sf::NonCopyable
{
public:

                                       Game();
                                       
    void                               run();
                                       
private:                               
                                       
    sf::RenderWindow                   window;
    sf::Clock                          clock;
    float                              deltaTime; // For framerate independence
    StringToKeyMap                     supportedKeys; // All keys that states can use
    std::stack<std::unique_ptr<State>> states;
    bool                               windowHasFocus;
                                       
                                       
    void                               updateDeltaTime();
    void                               processEvents();
    void                               update();
    void                               render();
                                       
    void                               initWindow();
    void                               initSupportedKeys();
    void                               initStates();

};


#endif // GAME_H
