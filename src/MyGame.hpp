/**
 * Header file for MyGame class.
 * @file MyGame.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef MYGAME_HPP
#define MYGAME_HPP

#include <vector>
#include <map>
#include <utility>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine/Game.hpp"
#include "Engine/json.hpp"

#include "Tile.hpp"
#include "TileTexture.hpp"

#include "Biomes.hpp"
#include "Camera.hpp"

class MyGame : public Game {

    private:

        Camera camera;

        TileTexture landTexture;
        TileTexture sandTexture;
        TileTexture waterFullTexture;
        TileTexture waterRightTexture;
        TileTexture waterLeftTexture;
        TileTexture waterTopTexture;
        TileTexture oneTreeTexture;
        TileTexture forestTexture;
        TileTexture undefinedTexture;
        TileTexture sandForestTexture;

        std::map<Biomes, std::vector< std::pair<Biomes, int> > > generationConstraints;
        std::map<Biomes, int > generationPriorities;

        int gridWidth;
        int gridHeight;

        bool showSelectedTile;
        
        std::vector< std::vector< Tile > > grid;

        void generateWorld();
        void mapTexturesToBiomes();
        TileTexture loadTextureFromJson(nlohmann::json, std::string);

        void display();
        void update();
        void handleInput(const SDL_Event&);

    public:
        MyGame(int = 800, int = 600, int = 30, int = 10);
        void setup();
        // void start();
        // void stop();
        // void destroy();
        

};

#endif // MYGAME_HPP