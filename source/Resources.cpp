#include "precompiled.h"
#include "Resources.h"


namespace resources
{


    const std::string fontsDirectory       = "Resources\\Fonts\\";
    const std::string tilemapsDirectory    = "Resources\\Maps\\";
    const std::string shadersDirectory     = "Resources\\Shaders\\";
    const std::string backgroundsDirectory = "Resources\\Images\\Backgrounds\\";
    const std::string enemiesDirectory     = "Resources\\Images\\Entities\\Enemies\\";
    const std::string playerDirectory      = "Resources\\Images\\Entities\\Player\\";
    const std::string weaponsDirectory     = "Resources\\Images\\Items\\Weapon\\";
    const std::string tilesDirectory       = "Resources\\Images\\Tiles\\";
    const std::string configDirectory      = "Config\\";


    std::string getFontFile()
    {
        return fontsDirectory + "Dosis-Light.ttf";
    }


    std::string getPixelFontFile()
    {
        return fontsDirectory + "PixellettersFull.ttf";
    }


    std::string getTilemapFile()
    {
        return tilemapsDirectory + "tilemap.txt";
    }


    std::string getFragmentShaderFile()
    {
        return shadersDirectory + "fragment_shader.frag";
    }


    std::string getVertexShaderFile()
    {
        return shadersDirectory + "vertex_shader.vert";
    }


    std::string getMainMenuBackgroundFile()
    {
        return backgroundsDirectory + "main_menu_bg.png";
    }


    std::string getRatTextureFile()
    {
        return enemiesDirectory + "rat_60x64.png";
    }


    std::string getPlayerTextureFile()
    {
        return playerDirectory + "player_sheet.png";
    }


    std::string getSwordTextureFile()
    {
        return weaponsDirectory + "sword.png";
    }


    std::string getTilesheetFile()
    {
        return tilesDirectory + "tilesheet.png";
    }


    std::string getGameStateKeybindsFile()
    {
        return configDirectory + "gamestate_keybinds.ini";
    }


    std::string getEditorStateKeybindsFile()
    {
        return configDirectory + "editorstate_keybinds.ini";
    }


    std::string getSupportedKeysFile()
    {
        return configDirectory + "supported_keys.ini";
    }


} // namespace resources
