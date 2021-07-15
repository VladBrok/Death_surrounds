#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"
#include "GameState.h"
#include "Button.h"


class MainMenuState: public State
{
public:

    MainMenuState(sf::RenderWindow* pWindow, 
                  const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                  std::stack<State*>* const pStates
                  );
    virtual ~MainMenuState();

    virtual void update(const float deltaTime);
    virtual void updateKeyboardInput(const float deltaTime);
    virtual void render(sf::RenderTarget* pTarget = nullptr);
    virtual void endState();

    void updateButtons();
    void renderButtons();

private:

    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Font font;
    std::unordered_map<std::string, Button*> buttons;

    void initFont();
    void initButtons();
    void initBackground();
};


#endif // MAIN_MENU_STATE_H
