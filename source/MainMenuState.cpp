#include "MainMenuState.h"
#include "EditorState.h"


MainMenuState::MainMenuState(sf::RenderWindow& window,
                             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                             std::stack<State*>* const pStates
                             )
    : State(window, pSupportedKeys, pStates)
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

    updateButtons();
}


void MainMenuState::updateKeyboardInput(const float deltaTime)
{
}


void MainMenuState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = &window;
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

    if (buttons["GAME_STATE"]->isPressed()) // Starting new game
    {
        pStates->push(new GameState(window, pSupportedKeys, pStates));
    }
    else if (buttons["EDITOR_STATE"]->isPressed()) // Going to editor state
    {
        pStates->push(new EditorState(window, pSupportedKeys, pStates));
    }
    else if (buttons["EXIT_STATE"]->isPressed()) // Exit the state
    {
        endActivity();
    }
}


void MainMenuState::renderButtons()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(window);
    }
}


void MainMenuState::initFont()
{
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
}


void MainMenuState::initButtons()
{
    const sf::Vector2f buttonSize(
        static_cast<float>(window.getSize().x / 7),
        static_cast<float>(window.getSize().y / 11)
    );
    const sf::Color textIdleColor(sf::Color(150, 150, 150));
    const sf::Color textHoverColor(sf::Color::White);
    const sf::Color textActiveColor(sf::Color(20, 20, 20, 200));

    buttons["GAME_STATE"] = new Button(window.getSize().x / 6.f, window.getSize().y / 2.3f, 
                                       buttonSize.x, buttonSize.y,
                                       font, 
                                       "New game",
                                       textIdleColor,
                                       textHoverColor,
                                       textActiveColor
                                       );

    buttons["SETTINGS_STATE"] = new Button(window.getSize().x / 6.f, window.getSize().y / 1.8f, 
                                           buttonSize.x, buttonSize.y,
                                           font, 
                                           "Settings",
                                           textIdleColor,
                                           textHoverColor,
                                           textActiveColor
                                           );
    buttons["EDITOR_STATE"] = new Button(window.getSize().x / 6.f, window.getSize().y / 1.5f, 
                                         buttonSize.x, buttonSize.y,
                                         font, 
                                         "Editor",
                                         textIdleColor,
                                         textHoverColor,
                                         textActiveColor
                                         );

    buttons["EXIT_STATE"] = new Button(window.getSize().x / 6.f, window.getSize().y / 1.15f, 
                                       buttonSize.x, buttonSize.y, 
                                       font, 
                                       "Quit",
                                       textIdleColor,
                                       textHoverColor,
                                       textActiveColor
                                       );
}


void MainMenuState::initBackground()
{
    background.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
    background.setTexture(&textures.at("BACKGROUND"));
}


void MainMenuState::initTextures()
{
    textures["BACKGROUND"].loadFromFile("Images\\Backgrounds\\main_menu_bg.png");
}