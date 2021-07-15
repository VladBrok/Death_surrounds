#include "MainMenuState.h"


MainMenuState::MainMenuState(sf::RenderWindow* pWindow,
                             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                             std::stack<State*>* const pStates
                             )
    : State(pWindow, pSupportedKeys, pStates)
{
    initTextures();
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
    updateMousePosition();

    updateKeyboardInput(deltaTime);
}


void MainMenuState::updateKeyboardInput(const float deltaTime)
{
    updateButtons();
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


void MainMenuState::updateButtons()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->update(mousePosView);
    }

    if (buttons["EXIT_STATE"]->isPressed()) // Exit the state
    {
        endActivity();
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
    const sf::Vector2i buttonSize(pWindow->getSize().x / 6, pWindow->getSize().y / 10);

    // Button width and height must be integers (otherwise the text will render badly)
    buttons["GAME_STATE"] = new Button(pWindow->getSize().x / 6.f, pWindow->getSize().y / 2.2f, 
                                       buttonSize.x, buttonSize.y,
                                       &font, "New game",
                                       sf::Color(70, 70, 70), sf::Color(150, 150, 150),
                                       sf::Color(20, 20, 20, 200)
                                       );

    buttons["SETTINGS_STATE"] = new Button(pWindow->getSize().x / 6.f, pWindow->getSize().y / 1.7f, 
                                           buttonSize.x, buttonSize.y,
                                           &font, "Settings",
                                           sf::Color(70, 70, 70), sf::Color(150, 150, 150),
                                           sf::Color(20, 20, 20, 200)
                                           );

    buttons["EXIT_STATE"] = new Button(pWindow->getSize().x / 6.f, pWindow->getSize().y / 1.25f, 
                                       buttonSize.x, buttonSize.y, 
                                       &font, "Quit",
                                       sf::Color(70, 70, 70), sf::Color(150, 150, 150),
                                       sf::Color(20, 20, 20, 200)
                                       );
}


void MainMenuState::initBackground()
{
    background.setSize(sf::Vector2f(pWindow->getSize().x, pWindow->getSize().y));
    background.setTexture(&textures.at("BACKGROUND"));
}


void MainMenuState::initTextures()
{
    textures["BACKGROUND"].loadFromFile("Images\\Backgrounds\\main_menu_bg.png");
}