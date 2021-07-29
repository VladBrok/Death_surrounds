#include "precompiled.h"
#include "MainMenuState.h"
#include "EditorState.h"
#include "GameState.h"
#include "SettingsState.h"
#include "GUI_functions.h"


MainMenuState::MainMenuState(sf::RenderWindow& window,
                             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                             std::stack<State*>* const pStates
                             )
    : State(window, pSupportedKeys, pStates)
{
    stateType = STATE_PROCESSES_EVENTS;

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


void MainMenuState::processEvent(const sf::Event& event)
{
    updateMousePosition();

    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->processEvent(event, mousePosWindow);
    }

    // Pushing new states if the corresponding button is pressed
    if (buttons["GAME_STATE"]->isPressed()) // Starting new game
    {
        pStates->push(new GameState(window, pSupportedKeys, pStates));
    }
    else if (buttons["SETTINGS_STATE"]->isPressed()) // Activating settings state
    {
        pStates->push(new SettingsState(window, pSupportedKeys, pStates));

        reinitialize();
    }
    else if (buttons["EDITOR_STATE"]->isPressed()) // Going to editor state
    {
        pStates->push(new EditorState(window, pSupportedKeys, pStates));
    }

    // Exiting from state
    else if (buttons["EXIT_STATE"]->isPressed())
    {
        endActivity();
    }
}


void MainMenuState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = &window;
    }
    pTarget->draw(background);

    renderButtons(*pTarget);
}


void MainMenuState::renderButtons(sf::RenderTarget& target)
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(target);
    }
}


void MainMenuState::initFont()
{
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
}


void MainMenuState::initButtons()
{
    const sf::Vector2u windowSize(window.getSize());

    const sf::Vector2f buttonSize(
        static_cast<float>(gui::percentToPixels(14.3f, windowSize.x)),
        static_cast<float>(gui::percentToPixels(9.f, windowSize.y))
    );
    const sf::Color textIdleColor(sf::Color(150, 150, 150));
    const sf::Color textHoverColor(sf::Color::White);
    const sf::Color textActiveColor(sf::Color(20, 20, 20, 200));

    buttons["GAME_STATE"] = new Button(gui::percentToPixels(16.7f, windowSize.x), 
                                       gui::percentToPixels(43.5f, windowSize.y), 
                                       buttonSize.x, 
                                       buttonSize.y,
                                       font, 
                                       "New game",
                                       textIdleColor,
                                       textHoverColor,
                                       textActiveColor
                                       );

    buttons["SETTINGS_STATE"] = new Button(gui::percentToPixels(16.7f, windowSize.x), 
                                           gui::percentToPixels(55.5f, windowSize.y), 
                                           buttonSize.x, 
                                           buttonSize.y,
                                           font, 
                                           "Settings",
                                           textIdleColor,
                                           textHoverColor,
                                           textActiveColor
                                           );
    buttons["EDITOR_STATE"] = new Button(gui::percentToPixels(16.7f, windowSize.x),
                                         gui::percentToPixels(66.6f, windowSize.y), 
                                         buttonSize.x, 
                                         buttonSize.y,
                                         font, 
                                         "Editor",
                                         textIdleColor,
                                         textHoverColor,
                                         textActiveColor
                                         );

    buttons["EXIT_STATE"] = new Button(gui::percentToPixels(16.7f, windowSize.x), 
                                       gui::percentToPixels(87.f, windowSize.y), 
                                       buttonSize.x, 
                                       buttonSize.y, 
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
    textures["BACKGROUND"].loadFromFile("Resources\\Images\\Backgrounds\\main_menu_bg.png");
}


void MainMenuState::reinitialize()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        delete b->second;
    } 

    initButtons();
    initBackground();
}