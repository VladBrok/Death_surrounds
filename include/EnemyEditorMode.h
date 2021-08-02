#ifndef ENEMYEDITORMODE_H
#define ENEMYEDITORMODE_H

#include "EditorMode.h"
#include "Tilemap.h"
#include "Button.h"
#include "TextureSelector.h"


class EnemyEditorMode: public EditorMode
{
public:
                                         EnemyEditorMode(sf::Font& font,
                                                         Tilemap& tilemap,
                                                         sf::RenderWindow& window,
                                                         sf::Vector2f& mousePosView,
                                                         sf::Vector2i& mousePosGrid,
                                                         std::unordered_map<std::string, sf::Keyboard::Key>& keybinds,
                                                         sf::View& view
                                                         );
    virtual void                         processEvent(const sf::Event& event);
    virtual void                         update(const float deltaTime);
    virtual void                         render(sf::RenderTarget& target);

private:

    sf::Font&                                           font;
    sf::View&                                           view;                                                   
    sf::RenderWindow&                                   window;
    sf::Vector2f&                                       mousePosView;
    sf::Vector2i&                                       mousePosGrid;
    std::unordered_map<std::string, sf::Keyboard::Key>& keybinds;

    // Tilemap
    Tilemap&                                            tilemap;
    sf::RectangleShape                                  tileSelector;
                                                        
    // Cursor text                                      
    sf::Text                                            cursorText;
                                                        
    // Private functions                                
    void                                 processTilemapEvent(const sf::Event& event);
    void                                 processKeyboardInputEvent(const sf::Event& event);
                                         
    void                                 updateView(const float deltaTime);
    void                                 updateCursorText();
      
    void                                 renderTilemap(sf::RenderTarget& target);
    void                                 renderTileSelectorAndCursorText(sf::RenderTarget& target);
                                         
    void                                 initTileSelector();
    void                                 initCursorText();
};


#endif // ENEMYEDITORMODE_H
