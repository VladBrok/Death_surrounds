#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"


const unsigned FPS_LIMIT = 60;


class Game
{
public:

    Game();
    ~Game();

    void run();

private:

    sf::RenderWindow window;
    sf::Clock clock;
    float deltaTime;
    std::unordered_map<std::string, sf::Keyboard::Key> supportedKeys;
    std::stack<State*> states;


    void updateDeltaTime();
    void processEvents();
    void update();
    void render();

    void initWindow();
    void initSupportedKeys();
    void initStates();

};


#endif // GAME_H
