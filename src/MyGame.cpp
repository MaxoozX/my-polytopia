/**
 * implementation file for MyGame class.
 * @file MyGame.cpp
 * @author Maxence
 * @version 1.0
*/

#include <stdexcept>
#include <utility>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <filesystem>
#include <fstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine/Game.hpp"
#include "Engine/Geometry.hpp"
#include "Engine/json.hpp"

#include "SpriteTexture.hpp"
#include "Tile.hpp"
#include "Biomes.hpp"

#include "MyGame.hpp"

#define HALF 0.5
#define TWO_THIRDS 0.66667

using TexturePtr = SDL_Texture*;
using namespace Geometry;
using AllowedAdj = std::map<Biomes, bool>;

using json = nlohmann::json;
namespace fs = std::filesystem;

template<typename T>
T min(T a, T b) {
    return (a < b) ? a : b;
}

template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

MyGame::MyGame(int windowWidth, int windowHeight, int framerate, int gridSize):
    Game::Game(windowWidth, windowHeight, framerate),
    camera(0, 0, windowWidth, windowHeight, windowWidth, windowHeight, -100, 121*gridSize, -200, 69*gridSize, 1.0),
    player(0, 0, NULL), // TODO: Random spawn location and set texture
    gridWidth(gridSize), gridHeight(gridSize),
    showSelectedTile(false), isZoomingIn(false), isZoomingOut(false),
    leftClickPress(false),
    grid(gridSize, std::vector<Tile>(gridSize, Tile()))
{
    generationConstraints = { // TODO: Add coefficients that change the probability of getting each element
        {Biomes::Water, {
            {Biomes::Sand, 1},
            {Biomes::Water, 1},
        }},
        {Biomes::Sand, {
            {Biomes::Land, 1},
            {Biomes::Sand, 1},
            {Biomes::Water, 1},
            {Biomes::SandForest, 1},
            {Biomes::LavaFloor, 1},
            // {Biomes::Volcano, 1},
        }},
        {Biomes::Land, {
            {Biomes::Tree, 1},
            {Biomes::Land, 1},
            {Biomes::Sand, 1},
        }},
        {Biomes::Tree, {
            {Biomes::Forest, 1},
            {Biomes::Tree, 1},
            {Biomes::Land, 1},
        }},
        {Biomes::Forest, {
            {Biomes::Forest, 1},
            {Biomes::Tree, 1},
            {Biomes::SandForest, 1},
        }},
        {Biomes::SandForest, {
            {Biomes::SandForest, 1},
            {Biomes::Sand, 1},
            {Biomes::Forest, 1},
        }},
        {Biomes::LavaFloor, {
            {Biomes::Volcano, 1},
            {Biomes::Sand, 1},
            {Biomes::LavaFloor, 1},
        }},
        {Biomes::Volcano, {
            {Biomes::LavaFloor, 1},
            // {Biomes::Sand, 1},
        }}
    };

    // If I want to change the terrain structure, it's here
    generationPriorities = { // TODO: I would have liked to change the probability depending on the neighbours
        // {Biomes::Water, 3},
        // {Biomes::Sand, 2},
        // {Biomes::Land, 2},
        // {Biomes::Tree, 1},
        // {Biomes::Forest, 1},
        // {Biomes::SandForest, 1},
        // {Biomes::LavaFloor, 1},
        // {Biomes::Volcano, 1},
        {Biomes::Water, 0},
        {Biomes::Sand, 0},
        {Biomes::Land, 1},
        {Biomes::Tree, 0},
        {Biomes::Forest, 0},
        {Biomes::SandForest, 0},
        {Biomes::LavaFloor, 0},
        {Biomes::Volcano, 0},
    };

    tilemapCurrentTexture = nullptr;

}

template<class T>
std::map<Biomes, T> MyGame::getBiomesMapDefaultVal(const T defaultValue) const {
    std::map<Biomes, T> newMap = {
        {Biomes::Water, defaultValue},
        {Biomes::Sand, defaultValue},
        {Biomes::Land, defaultValue},
        {Biomes::Tree, defaultValue},
        {Biomes::Forest, defaultValue},
        {Biomes::SandForest, defaultValue},
        {Biomes::LavaFloor, defaultValue},
        {Biomes::Volcano, defaultValue}
    };
    return newMap;
}

SpriteTexture MyGame::loadTextureFromJson(nlohmann::json textureJson, std::string textureIdentifier) {

    std::string textureName = textureJson["path"].get<std::string>();
    std::string texturePath = std::string("../assets/") + textureName;
    int textureWidth = textureJson["width"].get<int>();
    int textureHeight = textureJson["height"].get<int>();
    std::string textureAlphaStr = textureJson["alpha"].get<std::string>();
    double textureAlphaF = ::atof(textureAlphaStr.c_str());
    int textureAlpha = 255 * textureAlphaF;

    SpriteTexture newSpriteTexture;

    try {
        newSpriteTexture = SpriteTexture(m_renderer, textureWidth, textureHeight, texturePath, textureAlpha);
    } catch (std::invalid_argument& e) {
        SDL_Log("Problem loading %s : %s", textureIdentifier.c_str(), e.what());
    }

    return newSpriteTexture;

}

void MyGame::setup() {

    Game::setup();

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND); // Make sure our renderer can render transparency correctly
    SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "0"); // Make sure the textures are scaled properly    

    const std::filesystem::path configPath = "../assets/config.json";

    // Read JSON file
    std::ifstream file(configPath);
    json data;
    file >> data;

    json textures = data["textures"].get<json>();
    
    json landInfo = textures["land"].get<json>();
    landTexture = loadTextureFromJson(landInfo, "landTexture");

    json sandInfo = textures["sand"].get<json>();
    sandTexture = loadTextureFromJson(sandInfo, "sandTexture");

    json waterInfo = textures["water"].get<json>();

        json waterFullInfo = waterInfo["full"].get<json>();
        waterFullTexture = loadTextureFromJson(waterFullInfo, "waterFullTexture");

        json waterTopInfo = waterInfo["top"].get<json>();
        waterTopTexture = loadTextureFromJson(waterTopInfo, "waterTopTexture");

        json waterLeftInfo = waterInfo["left"].get<json>();
        waterLeftTexture = loadTextureFromJson(waterLeftInfo, "waterLeftTexture");

        json waterRightInfo = waterInfo["right"].get<json>();
        waterRightTexture = loadTextureFromJson(waterRightInfo, "waterRightTexture");

    json oneTreeInfo = textures["tree"].get<json>();
    oneTreeTexture = loadTextureFromJson(oneTreeInfo, "oneTreeTexture");

    json forestInfo = textures["forest"].get<json>();
    forestTexture = loadTextureFromJson(forestInfo, "forestTexture");

    json sandForestInfo = textures["sand-forest"].get<json>();
    sandForestTexture = loadTextureFromJson(sandForestInfo, "sandForestTexture");

    json volcanoInfo = textures["volcano"].get<json>();
    volcanoTexture = loadTextureFromJson(volcanoInfo, "volcanoTexture");

    json lavaFloorInfo = textures["lava-floor"].get<json>();
    lavaFloorTexture = loadTextureFromJson(lavaFloorInfo, "lavaFloorTexture");

    json undefinedInfo = textures["undefined"].get<json>();
    undefinedTexture = loadTextureFromJson(undefinedInfo, "undefinedTexture");

    json selectionCircleInfo = textures["selection-circle"].get<json>();
    selectionCircleTexture = loadTextureFromJson(selectionCircleInfo, "selectionCircleTexture");

    json splayerInfo = textures["character1"].get<json>();
    playerTexture = loadTextureFromJson(splayerInfo, "character1Texture");

    player.texture = &playerTexture;

    /*
    To improve performances, we will render the map on this texture only when there is a change, this way, there is no need to render a lot of tiles on every frame.
    */
    tilemapCurrentTexture = SDL_CreateTexture( m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 121*gridWidth+100, 69*gridHeight+200 );
    // FIXME: Hardcoded value, to change

    if(tilemapCurrentTexture == nullptr) {
        SDL_Log("There was a problem creating the tilemap texture : %s", SDL_GetError());
    }

    generateWorld();

    SDL_Log("This game is being made by Maxooz");
    SDL_Log("The game is ready.");

}

void MyGame::generateWorld() {

    std::uniform_int_distribution<int> chooseLand(1000);

    std::vector < std::vector < AllowedAdj > > allowedBiomes(
        gridHeight,
        std::vector< AllowedAdj >(
            gridWidth,
            getBiomesMapDefaultVal<bool>(true)
        )
    );

    std::vector < std::vector < int > > numberAllowedBiomes(
        gridHeight,
        std::vector< int >(
            gridWidth,
            5
        )
    );

    for(int col = 0; col < gridHeight; col++) {
        for(int row = 0; row < gridWidth; row++) {
            grid[col][row].setBiome(Biomes::Undefined);
        }
    }

    int toCompute = gridWidth * gridHeight;

    while (toCompute > 0) {

        toCompute -= 1;

        // Find the tile (still not computed) with the lowest entropy
        int minX = -1;
        int minY = -1;
        int lowestEntropy = 1000;
        for(int col = 0; col < gridHeight; col++) {
            for(int row = 0; row < gridWidth; row++) {
                if(grid[col][row].biome == Biomes::Undefined) {
                    const int curEntropy = numberAllowedBiomes[col][row];
                    if(curEntropy < lowestEntropy) {
                        minX = row;
                        minY = col;
                        lowestEntropy = curEntropy;
                    }
                    if(curEntropy == lowestEntropy && (chooseLand(m_randomRange) % 2) == 1) {
                        minX = row;
                        minY = col;
                        lowestEntropy = curEntropy;
                    }
                }
            }
        }

        if(minX < 0 || minY < 0) { // FIXME: Should never happen
            SDL_Log("There was a problem when looking for the tile with the lowest entropy");
        }

        // Choose one biome
        std::vector<Biomes> avaibleBiomes = {};
        for(auto it = allowedBiomes[minY][minX].begin(); it != allowedBiomes[minY][minX].end(); ++it) {
            auto key = it->first;
            auto value = it->second;

            if(value) {
                for(int i = 0; i < generationPriorities[key]; i++) { // Adding the biome multiple time if has a choosing priority
                    avaibleBiomes.push_back(key);
                }
            }
        }

        if(avaibleBiomes.empty()) { // FIXME: Should never happen
            SDL_Log("Apparently there are no biomes avaible...");
            SDL_Log("The algorithm has failed, it tries again.");
            return generateWorld();
            // TODO: Restart the algorithm or go back
        }

        // Set the new biome
        Biomes chosenBiome = avaibleBiomes[chooseLand(m_randomRange) % avaibleBiomes.size()];
        grid[minY][minX].setBiome(chosenBiome);

        // Set the allowed biome
        allowedBiomes[minY][minX] = getBiomesMapDefaultVal<bool>(false);
        allowedBiomes[minY][minX][chosenBiome] = true;

        Point2d<int> nextToCollapse = Point2d(minX, minY);

        std::vector<Point2d<int>> stillToCompute = {nextToCollapse};

        while(stillToCompute.empty() == false) {

            Point2d<int> curComputing = stillToCompute.front();
            stillToCompute.erase(stillToCompute.begin());

            // Find the biomes forbidden for the neighbours because of the new selected biome
            // ------------------------------------------------------------------------------

            AllowedAdj adjTilesAllowedBiomes = getBiomesMapDefaultVal<bool>(false);

            for(AllowedAdj::iterator it = allowedBiomes[curComputing.y][curComputing.x].begin(); it != allowedBiomes[curComputing.y][curComputing.x].end(); ++it)
            {
                auto key = it->first;
                auto value = it->second;

                if(value) {

                    for( auto allowedBiome : generationConstraints[key] ) {
                        adjTilesAllowedBiomes[allowedBiome.first] = true;
                    }

                }
            }
            // ------------------------------------------------------------------------------

            // At this point adjTilesAllowedBiomes contains all allowed biomes
            // Now we iterate it and if we have forbidden biomes we add this to our constraints
            // ------------------------------------------------------------------------------

            int topMoved = 0, bottomMoved = 0, leftMoved = 0, rightMoved = 0;

            for(AllowedAdj::iterator it = adjTilesAllowedBiomes.begin(); it != adjTilesAllowedBiomes.end(); ++it)
            {
                auto key = it->first; // <<--- points to your key
                auto value = it->second; // points to your value

                if(value == false) {
                    // For every neighbour
                    if(curComputing.y >= 1) {
                        if(allowedBiomes[curComputing.y - 1][curComputing.x][key]) {
                            numberAllowedBiomes[curComputing.y - 1][curComputing.x] -= 1;
                            topMoved++;
                        }
                        allowedBiomes[curComputing.y - 1][curComputing.x][key] = false;
                    }
                    if(curComputing.y < gridHeight - 1) {
                        if(allowedBiomes[curComputing.y + 1][curComputing.x][key]) {
                            numberAllowedBiomes[curComputing.y + 1][curComputing.x] -= 1;
                            bottomMoved++;
                        }
                        allowedBiomes[curComputing.y + 1][curComputing.x][key] = false;
                    }
                    if(curComputing.x >= 1) {
                        if(allowedBiomes[curComputing.y][curComputing.x - 1][key]) {
                            numberAllowedBiomes[curComputing.y][curComputing.x - 1] -= 1;
                        }
                        allowedBiomes[curComputing.y][curComputing.x - 1][key] = false;
                        leftMoved++;
                    }
                    if(curComputing.x < gridWidth - 1) {
                        if(allowedBiomes[curComputing.y][curComputing.x + 1][key]) {
                            numberAllowedBiomes[curComputing.y][curComputing.x + 1] -= 1;
                            rightMoved++;
                        }
                        allowedBiomes[curComputing.y][curComputing.x + 1][key] = false;
                    }
                }
            }
            // ------------------------------------------------------------------------------

            // If the neighbour has been changed, we add it to list to make sure its neighbours are computed as well
            // ------------------------------------------------------------------------------
            
            if(topMoved) { // Top
                Point2d<int> top(curComputing);
                top += Vector2d<int>(0, -1);
                stillToCompute.push_back(top);
            }

            if(bottomMoved) { // Bottom
                Point2d<int> bottom(curComputing);
                bottom += Vector2d<int>(0, +1);
                stillToCompute.push_back(bottom);
            }

            if(leftMoved) { // Left
                Point2d<int> left(curComputing);
                left += Vector2d<int>(-1, 0);
                stillToCompute.push_back(left);
            }

            if(rightMoved) { // Right
                Point2d<int> right(curComputing);
                right += Vector2d<int>(+1, 0);
                stillToCompute.push_back(right);
            }
            // ------------------------------------------------------------------------------
        }

        // Uncomment to see the map generation
        // --------------------------------------------------------------------------------
        // mapTexturesToBiomes();

        // display();
        // SDL_RenderPresent(m_renderer);
        // SDL_Delay(20);

        // --------------------------------------------------------------------------------

    }

    // Give every tile a texture
    mapTexturesToBiomes();
    
    updateTilemapTexture();

}

void MyGame::mapTexturesToBiomes() {
    for(int col = 0; col < gridHeight; col++) {
        for(int row = 0; row < gridWidth; row++) {

            switch (grid[col][row].biome) {
                case Biomes::Sand:
                    grid[col][row].setTexturePtr(&sandTexture);
                    break;

                case Biomes::Land:
                    grid[col][row].setTexturePtr(&landTexture);
                    break;

                case Biomes::Tree:
                    grid[col][row].setTexturePtr(&oneTreeTexture);
                    break;

                case Biomes::Forest:
                    grid[col][row].setTexturePtr(&forestTexture);
                    break;

                case Biomes::SandForest:
                    grid[col][row].setTexturePtr(&sandForestTexture);
                    break;

                case Biomes::LavaFloor:
                    grid[col][row].setTexturePtr(&lavaFloorTexture);
                    break;

                case Biomes::Volcano:
                    grid[col][row].setTexturePtr(&volcanoTexture);
                    break;

                case Biomes::Water:
                    grid[col][row].setTexturePtr(&waterTopTexture);

                    if((col + 1) == gridHeight) {
                        grid[col][row].setTexturePtr(&waterLeftTexture);
                    }

                    if((row + 1) == gridWidth) {
                        grid[col][row].setTexturePtr(&waterRightTexture);
                    }

                    if((col + 1) == gridHeight && (row + 1) == gridWidth) {
                        grid[col][row].setTexturePtr(&waterFullTexture);
                    }

                    break;

                default:
                    break;
            }
        }
    }
}

void MyGame::handleZoom() {

    const double zoomVal = 1.0 / gameFrameRate; // FIXME: Hardcoded, shouldn't be

    if(isZoomingIn) {
        camera.setZoom(camera.zoom + zoomVal);
    }
    if(isZoomingOut) {
        camera.setZoom(camera.zoom - zoomVal);
    }

}


void MyGame::handleCameraMovement() {

    // const double speed = 1000 / camera.zoom / gameFrameRate; // FIXME: Hardcoded, shouldn't be
    const double speed = std::round(500 / camera.zoom / gameFrameRate);

    Point2d<int> mouseAbsPos; // The absolute position on the screen
    Vector2d<int> windowTopLeftPos;

    SDL_GetGlobalMouseState(&mouseAbsPos.x, &mouseAbsPos.y);

    SDL_GetWindowPosition(window, &windowTopLeftPos.x, &windowTopLeftPos.y);

    mouseAbsPos -= windowTopLeftPos;

    // SDL_Log("%d %d", mouseAbsPos.x, mouseAbsPos.y);

    if(mouseAbsPos.x > gameWindowWidth) {
        camera.move(Vector2d<float>(speed, 0));
        showSelectedTile = false;
    }
    if(mouseAbsPos.x < 0) {
        camera.move(Vector2d<float>(-speed, 0));
        showSelectedTile = false;
    }
    if(mouseAbsPos.y > gameWindowHeight) {
        camera.move(Vector2d<float>(0, speed));
        showSelectedTile = false;
    }
    if(mouseAbsPos.y < 0) {
        camera.move(Vector2d<float>(0, -speed));
        showSelectedTile = false;
    }
}

void MyGame::update() {

    showSelectedTile = true;

    handleZoom();
    handleCameraMovement();

    display();
}

void MyGame::updateTilemapTexture() {

    SDL_SetRenderTarget(m_renderer, tilemapCurrentTexture); // From now on we are drawing on the texture

    if(SDL_GetRenderTarget(m_renderer) != tilemapCurrentTexture) { // Doesn't seem to be true
        SDL_Log("The target has not been set and is still the window");
        return;
    }

    // Set the background color to white
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    // Draw the cubes
    const int cubeWidth = 120; // FIXME: Add these as constants
    const int cubeHeight = 120;

    const int cubeWidthOffset = 120 * TWO_THIRDS; // FIXME: Hardcoded values, to change
    const int cubeHeightOffset = 120 * HALF;

    const int startX =  camera.worldRight / 2; // 12200 / 2; //(gameWindowWidth) / 2;
    const int startY = 400;

    const double a = TWO_THIRDS * cubeWidthOffset;
    const double b = -TWO_THIRDS * cubeWidthOffset;
    const double c = HALF * cubeHeightOffset;
    const double d = HALF * cubeHeightOffset;

    // const double i_hat[2] = {a, b}; // The distortion vector for the i vector
    // const double j_hat[2] = {c, d}; // The distortion vector for the j vector

    SDL_Rect cubeRect;
    cubeRect.w = cubeWidth;
    cubeRect.h = cubeHeight;
    cubeRect.x = 0;
    cubeRect.y = 0;

    for(int col = 0; col < gridHeight; col++) {
        for(int row = 0; row < gridWidth; row++) {

            Tile* curTile = &(grid[col][row]);
            SpriteTexture* curSpriteTexture = curTile->texture;

            if(curTile->biome == Biomes::Undefined) continue;

            int x = startX + (a * row + b * col);
            // int y = startY + (c * row + d * col) + (int)((row + col) * 4);
            int y = startY + (c * row + d * col);

            cubeRect.w = curSpriteTexture->width;
            cubeRect.h = curSpriteTexture->height;
            cubeRect.x = x - curSpriteTexture->width / 2;
            cubeRect.y = y - curSpriteTexture->height;

            SDL_RenderCopy(m_renderer, curSpriteTexture->texture, nullptr, &cubeRect);
            
        }
    }

    // Display the player
    int x = startX + (a * player.tileX + b * player.tileY);
    int y = startY + (c * player.tileX + d * player.tileY);

    cubeRect.w = player.texture->width;
    cubeRect.h = player.texture->height;
    cubeRect.x = x - player.texture->width / 2;
    cubeRect.y = y - player.texture->height;

    SDL_RenderCopy(m_renderer, player.texture->texture, nullptr, &cubeRect);

    SDL_RenderPresent(m_renderer);
    SDL_SetRenderTarget(m_renderer, NULL); // And we go back to drawing on the screen

    // SDL_Log("The current render target : %p (the tilemap : %p)", (void*)SDL_GetRenderTarget(m_renderer), (void*)tilemapCurrentTexture);

    // // Set the background color to white
    // SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    // SDL_RenderClear(m_renderer);

}

void MyGame::display() {

    // SDL_Log("The current render target : %p (the tilemap : %p)", (void*)SDL_GetRenderTarget(m_renderer), (void*)tilemapCurrentTexture);

    SDL_Rect tilemapRect = {0, 0, gameWindowWidth, gameWindowHeight};

    SDL_Rect tilemapInsideRect = {camera.x+100, camera.y+200, camera.w, camera.h}; // FIXME: Hardcoded values

    // Set the background color to white
    // SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, 255);
    // SDL_RenderClear(m_renderer);
    
    SDL_RenderCopy(m_renderer, tilemapCurrentTexture, &tilemapInsideRect, &tilemapRect);


    // Find the player's mouse position
    
    // TODO: Add these as constants
    const int cubeWidth = 120;
    const int cubeHeight = 120;

    const int cubeWidthOffset = cubeWidth * TWO_THIRDS;
    const int cubeHeightOffset = cubeHeight * HALF;

    const int startX =  camera.worldRight / 2; // 12200 / 2; //(gameWindowWidth) / 2;
    const int startY = 400;

    const double a = TWO_THIRDS * cubeWidthOffset;
    const double b = -TWO_THIRDS * cubeWidthOffset;
    const double c = HALF * cubeHeightOffset;
    const double d = HALF * cubeHeightOffset;

    SDL_Rect cubeRect;
    cubeRect.w = cubeWidth;
    cubeRect.h = cubeHeight;
    cubeRect.x = 0;
    cubeRect.y = 0;

    Point2d<int> mousePos;

    SDL_GetMouseState(&mousePos.x, &mousePos.y);

    mousePos = camera.getWorldCoordinates(mousePos);

    mousePos += Vector2d(100, 200); // That is here because of the offset we apply on the tilemap texture

    int mouseScreenXafterOffset = mousePos.x - startX;
    int mouseScreenYafterOffset = mousePos.y - startY + cubeHeight;

    // We use the inverse matrix to find the coordinates on the grid
    int actualMouseX = (mouseScreenXafterOffset * d + mouseScreenYafterOffset * (-b)) / (a*d - b*c);
    int actualMouseY = (mouseScreenXafterOffset * (-c) + mouseScreenYafterOffset * a) / (a*d - b*c);

    // int actualMouseX = max<int>(0,min<int>(gridWidth-1, actualMouseX_));
    // int actualMouseY = max<int>(0,min<int>(gridHeight-1, actualMouseY_));

    for(int col = 0; col < gridHeight; col++) {
        for(int row = 0; row < gridWidth; row++) {

            int x = startX + (a * row + b * col);
            // int y = startY + (cubeHeight) * TWO_THIRDS * (i_hat[1] * row + j_hat[1] * col); // Cool downward going effect
            int y = startY + (c * row + d * col);

            cubeRect.w = selectionCircleTexture.width;
            cubeRect.h = selectionCircleTexture.height;
            cubeRect.x = x - selectionCircleTexture.width / 2 - 100; // These offsets are here for the same reason the vector2d a few lines up
            cubeRect.y = y - selectionCircleTexture.height - 200;

            if(col == actualMouseY && row == actualMouseX && camera.transformRect(&cubeRect)) {
                SDL_RenderCopy(m_renderer, selectionCircleTexture.texture, nullptr, &cubeRect);
                if(leftClickPress) { // FIXME: It is at the wrong place, should be in the update function
                    player.tileX = actualMouseX;
                    player.tileY = actualMouseY;
                    leftClickPress = false;
                    updateTilemapTexture(); // FIXME: I absolutely don't want it to run multiple times per update, I should run it once at the end if necessary
                }
            }
            
        }
    }

}

void MyGame::handleInput(const SDL_Event &event) {
    switch (event.type) {

        case SDL_KEYDOWN:
            if (event.key.repeat == 0) {
                switch (event.key.keysym.sym) {

                    case SDLK_i:
                        isZoomingIn = true;
                        isZoomingOut = false;
                        break;

                    case SDLK_o:
                        isZoomingIn = false;
                        isZoomingOut = true;
                        break;

                    default:
                        break;
                }
            }
            break;

        case SDL_KEYUP:
            if (event.key.repeat == 0) {
                switch (event.key.keysym.sym) {

                case SDLK_i:
                    isZoomingIn = false;
                    break;

                case SDLK_o:
                    isZoomingOut = false;
                    break;

                default:
                    break;
                }
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            switch(event.button.button) {
                case SDL_BUTTON_LEFT:
                        leftClickPress = true;
                    break;
                default:
                    break;
            }

        case SDL_MOUSEBUTTONUP:
            switch(event.button.button) {
                case SDL_BUTTON_LEFT:

                    break;
                default:
                    break;
            }

        default:
            break;
    }
}

/*
void setup();
void start();
void stop();
void destroy();
void update();
void handleInput(const SDL_Event&);
*/