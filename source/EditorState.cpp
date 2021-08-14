#include "precompiled.h"
#include "EditorState.h"
#include "constants.h"
#include "Resources.h"


EditorState::EditorState(sf::RenderWindow& window,
                             const StringToKeyMap& supportedKeys,
                             std::stack<State*>& states
                             )
    : State(window, supportedKeys, states), 
      tilemap(TILEMAP_GRID_SIZE_MAX_X, TILEMAP_GRID_SIZE_MAX_Y),
      activeMode(0)
{
    stateType = STATE_UPDATES_AND_PROCESSES_EVENTS;

    initKeybinds(resources::getEditorStateKeybindsFile());
    initView();
    initFont();
    initModes();
    initGui();
}


EditorState::~EditorState()
{
    for (size_t i = 0; i < modes.size(); ++i)
    {
        delete modes[i];
    }

    delete pPauseMenu;
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
        pPauseMenu->render(*pTarget);
    }
}


void EditorState::processPauseMenuEvent(const sf::Event& event)
{
    pPauseMenu->processEvent(event, mousePosWindow);


    if (pPauseMenu->isButtonPressed("CONTINUE"))
    {
        unpauseState();
    }
    else if (pPauseMenu->isButtonPressed("LOAD"))
    {
        tilemap.loadFromFile(resources::getTilemapFile());
    }

    else if (pPauseMenu->isButtonPressed("SAVE"))
    {
        tilemap.saveToFile(resources::getTilemapFile());
    }

    else if (pPauseMenu->isButtonPressed("GO_TO_MAIN_MENU"))
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
    view.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
}



void EditorState::initFont()
{
    font.loadFromFile(resources::getFontFile());
}


void EditorState::initModes()
{
    modes.push_back(
        new DefaultEditorMode(font, tilemap, window, mousePosWindow, mousePosView, mousePosGrid, keybinds, view)
    );
}


void EditorState::initGui()
{
    pPauseMenu = new PauseMenu(window, font);

    pPauseMenu->addButton("CONTINUE", "Continue", 1);
    pPauseMenu->addButton("LOAD", "Load", 2);
    pPauseMenu->addButton("SAVE", "Save", 3);
    pPauseMenu->addButton("GO_TO_MAIN_MENU", "Go to main menu", 5);
}
