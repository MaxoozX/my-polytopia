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
#include "SpriteTexture.hpp"

#include "Biomes.hpp"
#include "Camera.hpp"
#include "Player.hpp"

class MyGame : public Game {

    private:

        Camera camera;

        // The biomes
        SpriteTexture landTexture;
        SpriteTexture sandTexture;
        SpriteTexture waterFullTexture;
        SpriteTexture waterRightTexture;
        SpriteTexture waterLeftTexture;
        SpriteTexture waterTopTexture;
        SpriteTexture oneTreeTexture;
        SpriteTexture forestTexture;
        SpriteTexture undefinedTexture;
        SpriteTexture sandForestTexture;
        SpriteTexture volcanoTexture;
        SpriteTexture lavaFloorTexture;

        // Other gameplay elements' textures
        SpriteTexture selectionCircleTexture;
        SpriteTexture playerTexture;

        SDL_Texture *tilemapCurrentTexture;

        Player player; // There may be several players in the future, but I will deal with that later

        std::map<Biomes, std::vector< std::pair<Biomes, int> > > generationConstraints;
        std::map<Biomes, int > generationPriorities;

        template<class T>
        std::map<Biomes, T> getBiomesMapDefaultVal(const T) const;

        int gridWidth;
        int gridHeight;

        bool showSelectedTile;
        bool isZoomingIn, isZoomingOut;
        bool leftClickPress;
        
        std::vector< std::vector< Tile > > grid;

        void generateWorld();
        void mapTexturesToBiomes();
        SpriteTexture loadTextureFromJson(nlohmann::json, std::string);

        void display();
        void updateTilemapTexture();


        void update();
        void handleZoom();
        void handleCameraMovement();
        void handleInput(const SDL_Event&);

    public:
        MyGame(int = 800, int = 600, int = 30, int = 10);
        void setup();
        // void start();
        // void stop();
        // void destroy();
        

};

#endif // MYGAME_HPP