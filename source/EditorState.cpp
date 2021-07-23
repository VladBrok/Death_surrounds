#include "precompiled.h"
#include "EditorState.h"
#include "constants.h"


EditorState::EditorState(sf::RenderWindow& window,
                             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                             std::stack<State*>* const pStates
                             )
    : State(window, pSupportedKeys, pStates), tileMap(10, 7, 1), textureSelector(GRID_SIZE / 2.f, GRID_SIZE / 2.f, GRID_SIZE * 10, GRID_SIZE * 2, tileMap.getTextureSheet())
{
    stateIsEventHandler = true;

    initKeybinds("Config//editorstate_keybinds.ini");
    initTextures();
    initButtons();
    initPauseMenu();
    initTextureRect();
    initTileSelector();
}


EditorState::~EditorState()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        delete b->second;
    }    

    delete pPauseMenu;
}


void EditorState::processEvents(const sf::Event& event)
{
    if (stateIsPaused)
    {
        processPauseMenuButtonEvents(event);
    }
    else
    {
        processButtonsEvent(event);

        processEditorEvent(event);

        updateTileSelector();
    }

    /* Pausing or unpausing the state */
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == keybinds.at("CLOSE_STATE"))
    {
        stateIsPaused ? unpauseState(): pauseState();
    }
}


void EditorState::processPauseMenuButtonEvents(const sf::Event& event)
{
    pPauseMenu->processMouseEvent(event, mousePosView);

    if (pPauseMenu->isButtonPressed("QUIT"))
    {
        endActivity();
    }
}


void EditorState::processButtonsEvent(const sf::Event& event)
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->processMouseEvent(event, mousePosView);
    }
}


void EditorState::processEditorEvent(const sf::Event& event)
{
    textureSelector.processEvent(event, mousePosWindow);

    // Making sure that we won't update anything else here if the texture selector is active
    if (textureSelector.isActive())
    {
        return;
    }


    if (event.type == sf::Event::MouseButtonPressed)
    {
        /* Adding the tile */
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            tileMap.addTile(mousePosGrid.x, mousePosGrid.y, 0, textureRect);
        }

        /* Removing the tile */
        else if (event.mouseButton.button == sf::Mouse::Right)
        {
            tileMap.removeTile(mousePosGrid.x, mousePosGrid.y, 0);
        }
    } 

    else if (event.type == sf::Event::KeyPressed)      
    {
        /* 
            Switching the texture by adjusting a value 
            of the textureRect.left
        */

        /* Switching to the next one */
        if (event.key.code == keybinds.at("NEXT_TEXTURE"))
        {
            textureRect.left >= (tileMap.getTextureSheet().getSize().x - (int)GRID_SIZE) ? (textureRect.left = 0): textureRect.left += (int)GRID_SIZE;
            tileSelector.setTextureRect(textureRect);
        }

        /* Switching to the previous one */
        else if (event.key.code == keybinds.at("PREVIOUS_TEXTURE"))
        {
            textureRect.left <= 0 ? (textureRect.left = tileMap.getTextureSheet().getSize().x - (int)GRID_SIZE): textureRect.left -= (int)GRID_SIZE;
            tileSelector.setTextureRect(textureRect);
        }
    }
}


void EditorState::update(const float deltaTime)
{
    updateMousePosition();
}


void EditorState::updateTileSelector()
{
    tileSelector.setPosition(mousePosGrid.x * GRID_SIZE, mousePosGrid.y * GRID_SIZE);
}


void EditorState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = &window;
    }


    tileMap.render(*pTarget);

    textureSelector.render(*pTarget);

    if (!textureSelector.isActive())
    {
        pTarget->draw(tileSelector);
    }


    if (stateIsPaused)
    {
        pPauseMenu->render(*pTarget);
    }
    else
    {
        renderButtons(*pTarget);
    }
}


void EditorState::renderButtons(sf::RenderTarget& target)
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(target);
    }
}


void EditorState::initButtons()
{
    //const sf::Vector2f buttonSize(
    //    static_cast<float>(pWindow->getSize().x / 6),
    //    static_cast<float>(pWindow->getSize().y / 10)
    //);
    //const sf::Color textIdleColor(sf::Color(150, 150, 150));
    //const sf::Color textHoverColor(sf::Color::White);
    //const sf::Color textActiveColor(sf::Color(20, 20, 20, 200));

    //buttons["GAME_STATE"] = new Button(pWindow->getSize().x / 6.f, pWindow->getSize().y / 2.2f, 
    //                                   buttonSize.x, buttonSize.y,
    //                                   &font, 
    //                                   "New game",
    //                                   textIdleColor,
    //                                   textHoverColor,
    //                                   textActiveColor
    //                                   );
}


void EditorState::initTextures()
{
    //textures["BACKGROUND"].loadFromFile("Images\\Backgrounds\\main_menu_bg.png");
}


void EditorState::initPauseMenu()
{
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
    pPauseMenu = new PauseMenu(window, font);

    pPauseMenu->addButton("QUIT", "Go to main menu", 5);
}


void EditorState::initTextureRect()
{
    textureRect.width  = static_cast<int>(GRID_SIZE);
    textureRect.height = static_cast<int>(GRID_SIZE);
}


void EditorState::initTileSelector()
{
    tileSelector.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
    tileSelector.setFillColor(sf::Color(255, 255, 255, 140));

    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::White);

    tileSelector.setTexture(&tileMap.getTextureSheet());
    tileSelector.setTextureRect(textureRect);
}
