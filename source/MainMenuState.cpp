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
    const sf::Vector2f buttonSize(
        static_cast<float>(pWindow->getSize().x / 6),
        static_cast<float>(pWindow->getSize().y / 10)
    );
    const sf::Color textIdleColor(sf::Color(150, 150, 150));
    const sf::Color textHoverColor(sf::Color::White);
    const sf::Color textActiveColor(sf::Color(20, 20, 20, 200));

    buttons["GAME_STATE"] = new Button(pWindow->getSize().x / 6.f, pWindow->getSize().y / 2.2f, 
                                       buttonSize.x, buttonSize.y,
                                       &font, 
                                       "New game",
                                       textIdleColor,
                                       textHoverColor,
                                       textActiveColor
                                       );

    buttons["SETTINGS_STATE"] = new Button(pWindow->getSize().x / 6.f, pWindow->getSize().y / 1.75f, 
                                           buttonSize.x, buttonSize.y,
                                           &font, 
                                           "Settings",
                                           textIdleColor,
                                           textHoverColor,
                                           textActiveColor
                                           );

    buttons["EXIT_STATE"] = new Button(pWindow->getSize().x / 6.f, pWindow->getSize().y / 1.3f, 
                                       buttonSize.x, buttonSize.y, 
                                       &font, 
                                       "Quit",
                                       textIdleColor,
                                       textHoverColor,
                                       textActiveColor
                                       );
}


void MainMenuState::initBackground()
{
    background.setSize(sf::Vector2f((float)pWindow->getSize().x, (float)pWindow->getSize().y));
    background.setTexture(&textures.at("BACKGROUND"));
}


void MainMenuState::initTextures()
{
    textures["BACKGROUND"].loadFromFile("Images\\Backgrounds\\main_menu_bg.png");
}