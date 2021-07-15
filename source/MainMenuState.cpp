#include "MainMenuState.h"


MainMenuState::MainMenuState(sf::RenderWindow* pWindow,
                             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                             std::stack<State*>* const pStates
                             )
    : State(pWindow, pSupportedKeys, pStates)
{
    initKeybinds("Config//main_menu_state_keybinds.ini");
    initFont();
    initButtons();
    initBackground();
}


MainMenuState::~MainMenuState()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        delete b->second;
    }    
}


void MainMenuState::update(const float deltaTime)
{
    updateActivityStatus();

    updateKeyboardInput(deltaTime);

    updateMousePosition();

    updateButtons();
}


void MainMenuState::updateKeyboardInput(const float deltaTime)
{
}


void MainMenuState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = pWindow;
    }
    pTarget->draw(background);

    renderButtons();
}


void MainMenuState::endState()
{
}


void MainMenuState::updateButtons()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->update(mousePosView);
    }

    if (buttons["EXIT_STATE"]->isPressed()) // Exit the state
    {
        stateIsActive = false;
    }
    else if (buttons["GAME_STATE"]->isPressed()) // Starting new game
    {
        pStates->push(new GameState(pWindow, pSupportedKeys, pStates));
    }
}


void MainMenuState::renderButtons()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(*pWindow);
    }
}


void MainMenuState::initFont()
{
    font.loadFromFile("Fonts\\PixellettersFull.ttf");
}


void MainMenuState::initButtons()
{
    // Button width and height must be integers (otherwise the text will render badly)
    buttons["GAME_STATE"] = new Button(pWindow->getSize().x / 6.f, pWindow->getSize().y / 2.f, 
                                       pWindow->getSize().x / 6, pWindow->getSize().y / 10,
                                       &font, "New game",
                                       sf::Color(70, 70, 70), sf::Color(150, 150, 150),
                                       sf::Color(20, 20, 20, 200)
                                       );

    buttons["EXIT_STATE"] = new Button(pWindow->getSize().x / 6.f, pWindow->getSize().y / 1.5f, 
                                       pWindow->getSize().x / 6, pWindow->getSize().y / 10, 
                                       &font, "Quit",
                                       sf::Color(70, 70, 70), sf::Color(150, 150, 150),
                                       sf::Color(20, 20, 20, 200)
                                       );
}


void MainMenuState::initBackground()
{
    background.setSize(sf::Vector2f(pWindow->getSize().x, pWindow->getSize().y));
    backgroundTexture.loadFromFile("Images\\Backgrounds\\main_menu_bg.png");
    background.setTexture(&backgroundTexture);
}