#include "precompiled.h"
#include "EnemyEditorMode.h"
#include "constants.h"


EnemyEditorMode::EnemyEditorMode(sf::Font& font,
                                 Tilemap& tilemap,
                                 sf::RenderWindow& window,
                                 sf::Vector2f& mousePosView,
                                 sf::Vector2i& mousePosGrid,
                                 std::unordered_map<std::string, sf::Keyboard::Key>& keybinds,
                                 sf::View& view
                                 )
  : font(font),
    tilemap(tilemap),
    window(window),
    mousePosView(mousePosView),
    mousePosGrid(mousePosGrid),
    keybinds(keybinds),
    view(view)
{
    initTileSelector();
    initCursorText();

    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
}


void EnemyEditorMode::processEvent(const sf::Event& event)
{
    processTilemapEvent(event);
    processKeyboardInputEvent(event);
}


void EnemyEditorMode::update(const float deltaTime)
{
    updateView(deltaTime);
    updateCursorText();
    tileSelector.setPosition(mousePosGrid.x * GRID_SIZE, mousePosGrid.y * GRID_SIZE);
}


void EnemyEditorMode::render(sf::RenderTarget& target)
{
    renderTilemap(target);
    renderTileSelectorAndCursorText(target);
}



void EnemyEditorMode::processTilemapEvent(const sf::Event& event)
{
    // Adding the enemy spawner
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        tilemap.addTile(mousePosGrid.x, mousePosGrid.y, 0, sf::IntRect(0.f, 0.f, 0.f, 0.f), false, ENEMY_SPAWNER);
    }

    // Removing the enemy spawner
    else if (event.type == sf::Event::MouseButtonPressed &&
             event.mouseButton.button == sf::Mouse::Right &&
             tilemap.getTileType(mousePosGrid.x, mousePosGrid.y, 0) == ENEMY_SPAWNER
             )
    {
        tilemap.removeTile(mousePosGrid.x, mousePosGrid.y, 0);
    } 
}


void EnemyEditorMode::processKeyboardInputEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == keybinds.at("TILE_COLLISION"))
        {
            
        }

        else if (event.key.code == keybinds.at("TILE_TYPE"))
        {

        }
    }
}


void EnemyEditorMode::updateView(const float deltaTime)
{
    const float viewSpeed = 360.f * deltaTime;

    if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_VIEW_UP")))
    {
        view.move(0.f, -viewSpeed);

        // Adjusting the view vertical position 
        if (view.getCenter().y - view.getSize().y / 2.f < 0.f)
        {
            view.setCenter(view.getCenter().x, view.getSize().y / 2.f);
        }
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_VIEW_DOWN")))
    {
        view.move(0.f, viewSpeed);
    }
    if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_VIEW_LEFT")))
    {
        view.move(-viewSpeed, 0.f);

        // Adjusting the view horizontal position
        if (view.getCenter().x - view.getSize().x / 2.f < 0.f)
        {
            view.setCenter(view.getSize().x / 2.f, view.getCenter().y);
        }
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_VIEW_RIGHT")))
    {
        view.move(viewSpeed, 0.f);
    }
}


void EnemyEditorMode::updateCursorText()
{
    int activeLayer = 0; // The active layer of the tilemap (grid position in the z-axis)

    std::stringstream sstream;
    sstream << "Grid position:     (" << mousePosGrid.x << ';' << mousePosGrid.y << ")\n";
    sstream << "Enemy type:         " << "NONE" << '\n';
    sstream << "Enemy amount:             " << "NONE" << '\n';
    sstream << "Time to spawn:      " << "NONE" << '\n';
    sstream << "Max distance:       " << "NONE" << '\n';

    cursorText.setString(sstream.str());
    cursorText.setPosition(mousePosView.x + 15.f, mousePosView.y);
}


void EnemyEditorMode::renderTilemap(sf::RenderTarget& target)
{
    target.setView(view);

    tilemap.render(target, mousePosGrid, nullptr, sf::Vector2f(), true);
    tilemap.renderDeferred(target);

    target.setView(target.getDefaultView());
}


void EnemyEditorMode::renderTileSelectorAndCursorText(sf::RenderTarget& target)
{
    target.setView(view);
    target.draw(tileSelector);
    target.draw(cursorText);
    target.setView(window.getDefaultView());
}


void EnemyEditorMode::initTileSelector()
{
    tileSelector.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
    tileSelector.setFillColor(sf::Color(255, 255, 255, 30));

    tileSelector.setOutlineThickness(3.f);
    tileSelector.setOutlineColor(sf::Color::Magenta);
}


void EnemyEditorMode::initCursorText()
{
    cursorText.setCharacterSize(window.getSize().y / 35);
    cursorText.setFont(font);
}
