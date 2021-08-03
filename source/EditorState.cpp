#include "precompiled.h"
#include "EditorState.h"
#include "constants.h"


EditorState::EditorState(sf::RenderWindow& window,
                             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                             std::stack<State*>* const pStates
                             )
    : State(window, pSupportedKeys, pStates), 
      tilemap(TILEMAP_GRID_SIZE_X, TILEMAP_GRID_SIZE_Y, TILEMAP_GRID_SIZE_Z),
      activeMode(0)
{
    stateType = STATE_UPDATES_AND_PROCESSES_EVENTS;

    initKeybinds("Config//editorstate_keybinds.ini");
    initView();
    initFont();
    initModes();
    initPauseMenu();
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

    // Pausing or unpausing the state
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


    if (pPauseMenu->isButtonPressed("LOAD"))
    {
        tilemap.loadFromFile("Resources\\Data\\tile_map.txt");
    }

    else if (pPauseMenu->isButtonPressed("SAVE"))
    {
        tilemap.saveToFile("Resources\\Data\\tile_map.txt");
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
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
}


void EditorState::initModes()
{
    modes.push_back(
        new DefaultEditorMode(font, tilemap, window, mousePosWindow, mousePosView, mousePosGrid, keybinds, view)
    );
}


void EditorState::initPauseMenu()
{
    pPauseMenu = new PauseMenu(window, font);

    pPauseMenu->addButton("LOAD", "Load", 2);

    pPauseMenu->addButton("SAVE", "Save", 3);

    pPauseMenu->addButton("GO_TO_MAIN_MENU", "Go to main menu", 5);
}
