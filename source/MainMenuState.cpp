#include "precompiled.h"
#include "MainMenuState.h"
#include "EditorState.h"
#include "GameState.h"
#include "SettingsState.h"
#include "Utils.h"
#include "Resources.h"


MainMenuState::MainMenuState(sf::RenderWindow& window,
                             const StringToKeyMap& supportedKeys,
                             std::stack<std::unique_ptr<State>>& states
                             )
    : State(window, supportedKeys, states), 
      needToReinitialize(false)
{
    initTextures();
    initGui();
    initBackground();
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
        std::unique_ptr<State> state(new GameState(window, supportedKeys, states));
        states.push(std::move(state));
    }
    else if (buttons["SETTINGS_STATE"]->isPressed()) // Activating the settings state
    {
        std::unique_ptr<State> state(new SettingsState(window, supportedKeys, states, needToReinitialize));
        states.push(std::move(state));
    }
    else if (buttons["EDITOR_STATE"]->isPressed()) // Going to the editor state
    {
        std::unique_ptr<State> state(new EditorState(window, supportedKeys, states));
        states.push(std::move(state));
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

    buttons["GAME_STATE"].reset(
        new Button(
               utils::percentToPixels(16.7f, windowSize.x), 
               utils::percentToPixels(43.5f, windowSize.y), 
               buttonSize.x, 
               buttonSize.y,
               font, 
               "New game",
               textIdleColor,
               textHoverColor,
               textActiveColor
        )
    );
    buttons["SETTINGS_STATE"].reset(
        new Button(
               utils::percentToPixels(16.7f, windowSize.x), 
               utils::percentToPixels(55.5f, windowSize.y), 
               buttonSize.x, 
               buttonSize.y,
               font, 
               "Settings",
               textIdleColor,
               textHoverColor,
               textActiveColor
        )
    );
    buttons["EDITOR_STATE"].reset(
        new Button(
               utils::percentToPixels(16.7f, windowSize.x),
               utils::percentToPixels(66.6f, windowSize.y), 
               buttonSize.x, 
               buttonSize.y,
               font, 
               "Editor",
               textIdleColor,
               textHoverColor,
               textActiveColor
        )
    );
    buttons["EXIT_STATE"].reset(
        new Button(
              utils::percentToPixels(16.7f, windowSize.x), 
              utils::percentToPixels(87.f, windowSize.y), 
              buttonSize.x, 
              buttonSize.y, 
              font, 
              "Quit",
              textIdleColor,
              textHoverColor,
              textActiveColor
        )
    );
}


void MainMenuState::initBackground()
{
    background.setSize(sf::Vector2f(window.getSize()));
    background.setTexture(&textures.at("BACKGROUND"));
}


void MainMenuState::initTextures()
{
    textures["BACKGROUND"].loadFromFile(resources::getMainMenuBackgroundFile());
}


void MainMenuState::reinitialize()
{
    buttons.clear();

    initGui();
    initBackground();
}