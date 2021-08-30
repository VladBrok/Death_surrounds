#include "precompiled.h"
#include "EditorState.h"
#include "constants.h"
#include "Resources.h"


EditorState::EditorState(sf::RenderWindow& window,
                         const StringToKeyMap& supportedKeys,
                         std::stack<std::unique_ptr<State>>& states
                         )
    : State(window, supportedKeys, states), 
      tilemap(TILEMAP_GRID_SIZE_MAX_X, TILEMAP_GRID_SIZE_MAX_Y),
      activeMode(0)
{
    initKeybinds(resources::getEditorStateKeybindsFile());
    initView();
    initModes();
    initGui();
}


void EditorState::processEvent(const sf::Event& event)
{
    if (stateIsPaused)
    {
        processPauseMenuEvent(event);
    }
    else
    {   
        processKeyboardEvent(event);
        modes[activeMode]->processEvent(event);
    }

    // Pausing / unpausing the state
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == keybinds.at("PAUSE"))
    {
        stateIsPaused ? unpauseState(): pauseState();
    }
}


void EditorState::update(const float deltaTime)
{
    updateMousePosition(&view);

    modes[activeMode]->update(deltaTime);
}


void EditorState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = &window;
    }

    
    modes[activeMode]->render(*pTarget);

    if (stateIsPaused)
    {
        pauseMenu->render(*pTarget);
    }
}


void EditorState::processPauseMenuEvent(const sf::Event& event)
{
    pauseMenu->processEvent(event, mousePosWindow);


    if (pauseMenu->isButtonPressed("CONTINUE"))
    {
        unpauseState();
    }
    else if (pauseMenu->isButtonPressed("LOAD"))
    {
        tilemap.loadFromFile(resources::getTilemapFile());
    }

    else if (pauseMenu->isButtonPressed("SAVE"))
    {
        tilemap.saveToFile(resources::getTilemapFile());
    }

    else if (pauseMenu->isButtonPressed("GO_TO_MAIN_MENU"))
    {
        endActivity();
    }
}


void EditorState::processKeyboardEvent(const sf::Event& event)
{
    // Switching between modes
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == keybinds.at("NEXT_EDITOR_MODE"))
        {
            (activeMode + 1 >= (int)modes.size()) ? (activeMode = 0): (++activeMode);
        }
        else if (event.key.code == keybinds.at("PREVIOUS_EDITOR_MODE"))
        {
            (activeMode - 1 < 0) ? (activeMode = modes.size() - 1): (--activeMode);
        }
    }
}


void EditorState::initView()
{
    view.setSize(sf::Vector2f(window.getSize());
}


void EditorState::initModes()
{
    std::unique_ptr<DefaultEditorMode> mode(
        new DefaultEditorMode(
               font, 
               tilemap,
               window, 
               mousePosWindow, 
               mousePosView,
               mousePosGrid,
               keybinds, 
               view
        )
    );
    modes.push_back(std::move(mode));
}


void EditorState::initGui()
{
    pauseMenu.reset(new PauseMenu(window, font));

    pauseMenu->addButton("CONTINUE", "Continue", 1);
    pauseMenu->addButton("LOAD", "Load", 2);
    pauseMenu->addButton("SAVE", "Save", 3);
    pauseMenu->addButton("GO_TO_MAIN_MENU", "Go to main menu", 5);
}
