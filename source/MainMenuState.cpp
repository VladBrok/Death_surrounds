#include "precompiled.h"
#include "MainMenuState.h"
#include "EditorState.h"
#include "GameState.h"
#include "SettingsState.h"
#include "Utils.h"
#include "Resources.h"


MainMenuState::MainMenuState(sf::RenderWindow& window,
                             const StringToKeyMap& supportedKeys,
                             std::stack<State*>& states
                             )
    : State(window, supportedKeys, states), needToReinitialize(false)
{
    stateType = STATE_PROCESSES_EVENTS;

    initTextures();
    initGui();
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
        states.push(new GameState(window, supportedKeys, states));
    }
    else if (buttons["SETTINGS_STATE"]->isPressed()) // Activating the settings state
    {
        states.push(new SettingsState(window, supportedKeys, states, needToReinitialize));
    }
    else if (buttons["EDITOR_STATE"]->isPressed()) // Going to the editor state
    {
        states.push(new EditorState(window, supportedKeys, states));
    }

    
    else if (buttons["EXIT_STATE"]->isPressed()) // Exiting from the state
    {
        endActivity();
    }

    if (needToReinitialize)
    {
        needToReinitialize = false;
        reinitialize();
    }
}


void MainMenuState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = &window;
    }
    pTarget->draw(background);

    renderGui(*pTarget);
}


void MainMenuState::renderGui(sf::RenderTarget& target)
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(target);
    }
}


void MainMenuState::initGui()
{
    const sf::Vector2u windowSize(window.getSize());


    /*=============== Buttons ===============*/

    const sf::Vector2f buttonSize(
        static_cast<float>(utils::percentToPixels(14.3f, windowSize.x)),
        static_cast<float>(utils::percentToPixels(9.f, windowSize.y))
    );
    const sf::Color textIdleColor(sf::Color(150, 150, 150));
    const sf::Color textHoverColor(sf::Color::White);
    const sf::Color textActiveColor(sf::Color(20, 20, 20, 200));

    buttons["GAME_STATE"] = new Button(utils::percentToPixels(16.7f, windowSize.x), 
                                       utils::percentToPixels(43.5f, windowSize.y), 
                                       buttonSize.x, 
                                       buttonSize.y,
                                       font, 
                                       "New game",
                                       textIdleColor,
                                       textHoverColor,
                                       textActiveColor
                                       );

    buttons["SETTINGS_STATE"] = new Button(utils::percentToPixels(16.7f, windowSize.x), 
                                           utils::percentToPixels(55.5f, windowSize.y), 
                                           buttonSize.x, 
                                           buttonSize.y,
                                           font, 
                                           "Settings",
                                           textIdleColor,
                                           textHoverColor,
                                           textActiveColor
                                           );
    buttons["EDITOR_STATE"] = new Button(utils::percentToPixels(16.7f, windowSize.x),
                                         utils::percentToPixels(66.6f, windowSize.y), 
                                         buttonSize.x, 
                                         buttonSize.y,
                                         font, 
                                         "Editor",
                                         textIdleColor,
                                         textHoverColor,
                                         textActiveColor
                                         );

    buttons["EXIT_STATE"] = new Button(utils::percentToPixels(16.7f, windowSize.x), 
                                       utils::percentToPixels(87.f, windowSize.y), 
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
    textures["BACKGROUND"].loadFromFile(resources::getMainMenuBackgroundFile());
}


void MainMenuState::reinitialize()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        delete b->second;
    } 

    initGui();
    initBackground();
}