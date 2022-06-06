/**
 * implementation file for base Tetris class.
 * @file Tetris.cpp
 * @author Maxence
 * @version 1.0
*/

#include <cmath>
#include <random>
#include <algorithm>
#include <utility>
#include <string>
#include <filesystem>
#include <fstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine/Game.hpp"
#include "Engine/json.hpp"

#include "constants.hpp"
#include "exceptions.hpp"
#include "Block.hpp"

#include "Tetris.hpp"

using blocksIterator = std::vector< Block* >::iterator;

using json = nlohmann::json;
namespace fs = std::filesystem;

Tetris::Tetris(int windowWidth, int windowHeight, int frameRate, int maxBlockIndex, int boardOffsetX, int boardOffsetY, Constants* ptrConstants): 
    Game::Game(windowWidth, windowHeight, frameRate),
    m_currentBlock(nullptr), m_nextBlock(nullptr), m_blocks(),
    blockChoice(1, maxBlockIndex), possibleShapes(),
    spaceBarPressed(false), leftArrowPressed(false), rightArrowPressed(false), bottomArrowPressed(false),
    lastMove(0), lastDownMove(0),
    widthCells(ptrConstants->WIDTH_IN_CELLS), heightCells(ptrConstants->HEIGHT_IN_CELLS),
    tilesPerLines(ptrConstants->HEIGHT_IN_CELLS, 0),
    score(0), digitsTextures(10, nullptr), backgroundTheme(nullptr),
    faceTextures(10, nullptr),
    backgroundColor(0,0,0,1.0), m_boardOffsetX(boardOffsetX), m_boardOffsetY(boardOffsetY),
    displayFaces(false), constants(ptrConstants)
    {}

void Tetris::setup() {

    Game::setup();

    // Read the value of faces
    const std::filesystem::path configPath = constants->assetsPath / "config.json";
    if(!fs::exists(configPath)) {
        SDL_Log("Impossible to find the configuration file at %s", configPath.string().c_str());
        throw std::runtime_error("Impossible to load data file");
    }

    // Read JSON file
    std::ifstream file(configPath);
    json data;
    file >> data;

    displayFaces = data["faces"].get<bool>();

    loadDigitsTextures();
    loadBackgroundTextures();
    loadFaceTextures();

    m_currentBlock = newBlock();

    SDL_Log("This game is provided by Maxooz");
    SDL_Log("The game is ready.");

}

void Tetris::replay() {

    SDL_Log("Trying to replay");

    // reset the variables
    m_currentBlock = nullptr;
    m_nextBlock = nullptr;
    m_blocks.clear();
    possibleShapes.clear();
    spaceBarPressed = false, leftArrowPressed = false, rightArrowPressed = false, bottomArrowPressed = false;
    lastMove = 0, lastDownMove = 0;
    tilesPerLines = std::vector<int>(constants->HEIGHT_IN_CELLS, 0);
    score = 0;

    m_currentBlock = newBlock();

    // Call the start function
    start();

}

void Tetris::gameover() {

    SDL_Log("GAME OVER");

    bool wannaReplay = false;

    // while loop
    while((!wannaReplay) && (!quit)) {

        lastTime = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            } else if(event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                // anykey press
                wannaReplay = true;
            }
        }

        display();

        // draw gameover overlay
        SDL_Rect windowRect;
        windowRect.x = 0;
        windowRect.y = (int)(sin(lastTime/200)*5); // To make the gameover text a bit bumpy
        windowRect.w = gameWindowWidth;
        windowRect.h = gameWindowHeight;

        SDL_RenderCopy(m_renderer, gameoverOverlay, nullptr, &windowRect);

        SDL_RenderPresent(m_renderer);

        timeElapsed = SDL_GetTicks() - lastTime; // In ms
        timeToWait = timePerFrame - timeElapsed;

        if (timeToWait > 0) {
            SDL_Delay(timeToWait);
        }

    }
    // SDL_Log("Loop ended");
    if(wannaReplay) replay();

}

void Tetris::loadFaceTextures() {

    const std::filesystem::path facesPath = constants->assetsPath / "background";

    // Should load from 0 to 9

    for(int i = 0; i < 10; i++) {

        const std::filesystem::path facePath = facesPath / (std::to_string(i) + ".png");
        if(!std::filesystem::exists(facePath)) {
            SDL_Log("The face file : %s doesn't exist.", facePath.string().c_str());
        }

        faceTextures[i] = IMG_LoadTexture(m_renderer, facePath.string().c_str());

        if(faceTextures[i] == nullptr) {
            SDL_Log("Problem loading the face : %d (%s)", i, IMG_GetError());
        }

    }

}

void Tetris::loadBackgroundTextures() {

    // backgroundTheme

    const std::filesystem::path backgroundThemePath = constants->assetsPath / "backgroundTheme.png";
    const std::string backgroundThemePathString = backgroundThemePath.string();
    const char* backgroundThemePathCStr = backgroundThemePathString.c_str();

    backgroundTheme = IMG_LoadTexture(m_renderer, backgroundThemePathCStr);
    if(backgroundTheme == nullptr) {
        SDL_Log("Problem loading the background theme (%s)", IMG_GetError());
    }

    const std::filesystem::path gameoverOverlayPath = constants->assetsPath / "gameoverOverlay.png";
    const std::string gameoverOverlayPathString = gameoverOverlayPath.string();
    const char* gameoverOverlayPathCStr = gameoverOverlayPathString.c_str();

    gameoverOverlay = IMG_LoadTexture(m_renderer, gameoverOverlayPathCStr);
    if(gameoverOverlay == nullptr) {
        SDL_Log("Problem loading the gameover overlay (%s)", IMG_GetError());
    }

}

void Tetris::loadDigitsTextures() {

    const std::filesystem::path digitsPath = constants->assetsPath / "digits";    

    for(int i = 0; i < 10; i++) {

        const std::filesystem::path digitPath = digitsPath / (std::to_string(i) + ".png");
        const std::string digitPathString = digitPath.string();
        const char* digitPathCStr = digitPathString.c_str();

        digitsTextures[i] = IMG_LoadTexture(m_renderer, digitPathCStr);
        if(digitsTextures[i] == nullptr) {
            SDL_Log("Problem loading the texture of the number %d (%s)", i, IMG_GetError());
        }
        SDL_SetTextureColorMod(digitsTextures[i], 255, 255, 255);
    }
}

Block* Tetris::newBlock() {

    // Fill up the array
    if(possibleShapes.size() <= 0) {
        possibleShapes = {1, 2, 3, 4, 5, 6, 7};
    }

    // Pick a random element still in the array
    unsigned int choice = 8;
    while(choice >= possibleShapes.size()) {
        choice = blockChoice(mt) - 1;
    }

    int shapeIndex = possibleShapes[choice];

    // Remove the element from the array
    possibleShapes.erase(possibleShapes.begin() + choice);

    // newBlock -> nextBlock
    // nextBlock -> currentBlock
    if(m_nextBlock == nullptr) {
        m_nextBlock = new Block(m_renderer, widthCells, heightCells, 3, 5, blockChoice(mt), &faceTextures, constants);
        m_nextBlock->load();
    }

    Block* newBlock = m_nextBlock;

    m_nextBlock = new Block(m_renderer, widthCells, heightCells, 3, 5, shapeIndex, &faceTextures, constants);
    
    m_nextBlock->load();

    // SDL_Log("New block : w: %d, h: %d", newBlock->m_width, newBlock->m_height);

    newBlock->m_x = widthCells/2;
    newBlock->m_y = 1;

    return newBlock;

}

void Tetris::update() {

    int currentTime = SDL_GetTicks();

    if(m_currentBlock == nullptr) throw err::NoCurrentBlock();

    if(spaceBarPressed) {
        rotateCurrentBlock();
        spaceBarPressed = false;
    }

    double difficulyFactor = pow(0.93, log2(score>0?(float)score:1.0f));

    bool playerCanMove = (currentTime - lastMove) > (1000 / constants->MOVES_SECOND);
    bool pieceShouldMoveDown = (bottomArrowPressed)
        ? (currentTime - lastDownMove) > (1000 / constants->DOWN_MOVES_SECOND * difficulyFactor) / 4
        : (currentTime - lastDownMove) > (1000 / constants->DOWN_MOVES_SECOND * difficulyFactor);

    if(playerCanMove) {
        moveCurrentBlockSide();
    }

    if(pieceShouldMoveDown && !moveCurrentBlockDown()) {

        m_blocks.push_back(m_currentBlock);

        // Take the new block in account
        for(int row = 0; row < m_currentBlock->m_height; row++) {
            tilesPerLines[row + m_currentBlock->m_y] += m_currentBlock->getNbTilesRow(row);
        }

        int linesCompleted = 0;

        // The problem is that m_currentBlock is in m_blocks
        // so, we need to consider it a fixed block, and not require anything to it
        int minRowToCheck = m_currentBlock->m_y;

        for(
            int row = m_currentBlock->m_y + m_currentBlock->m_trueBottom; // Starts at the end to prevent undefined shape behavior
            row >= minRowToCheck;
        ) {
            // SDL_Log("Lines [%d] : %d", row, tilesPerLines[row]);
            if(row < heightCells && tilesPerLines[row] >= widthCells) {
                linesCompleted++;
                // SDL_Log("Removing row : %d", row);
                
                for(auto&& block : m_blocks) {
                    if(row >= block->m_y && row <= (block->m_y + block->m_trueBottom)) {

                        bool blockUseless = block->removeRow(row - block->m_y);

                        if(blockUseless) {
                            delete block;
                            block = nullptr;
                            continue;
                        }

                    }

                    if(row > block->m_y + block->m_trueBottom) {
                        block->m_y++; // FIXME: The blocks are not deleted and are still visible
                    }
                }

                m_blocks.erase(std::remove(begin(m_blocks), end(m_blocks), nullptr), end(m_blocks));

                tilesPerLines.erase(tilesPerLines.begin() + row);
                tilesPerLines.insert(tilesPerLines.begin(), 0);

            } else {
                row--;
            }
        }

        /*
        Basic scoring system
        lines : 1->40, 2->100, 3->300, 4->1200
        */
        switch(linesCompleted) {

            case 1:
                score += 40;
                break;

            case 2:
                score += 100;
                break;

            case 3:
                score += 300;
                break;

            case 4:
                score += 1200;
                break;

            default:
                break;

        }

        // is the player losing

        if(tilesPerLines[5] > 0) {
            gameover();
        }

        m_currentBlock = newBlock();
    }

    display();

}

void Tetris::display() {

    SDL_Rect windowRect;
    windowRect.x = 0;
    windowRect.y = 0;
    windowRect.w = gameWindowWidth;
    windowRect.h = gameWindowHeight;

    SDL_RenderCopy(m_renderer, backgroundTheme, nullptr, &windowRect);


    for(Block* loopCurBlock : m_blocks) {
        loopCurBlock->draw(m_boardOffsetX, m_boardOffsetY, !displayFaces);
    }
    m_currentBlock->draw(m_boardOffsetX, m_boardOffsetY, !displayFaces);
    m_nextBlock->draw(0, 0, true);


    std::string scoreStr = std::to_string(score);
    int nbDigits = scoreStr.length();

    SDL_Rect digitRect;
    digitRect.h = constants->DIGIT_H;
    digitRect.w = constants->DIGIT_W;
    digitRect.x = constants->DIGIT_X0;
    digitRect.y = constants->DIGIT_Y0;

    for(int index = 0; index < nbDigits; index++, digitRect.x += constants->DIGIT_OFFSET) {

        char curChar = scoreStr[index];
        int actualNumber = curChar - 48;

        SDL_RenderCopy(m_renderer, digitsTextures[actualNumber], nullptr, &digitRect);

    }

}

bool Tetris::rotateCurrentBlock() {

    if(m_currentBlock->m_shapeIndex == constants->PIECE_O) {

        return true;

    } else if(m_currentBlock->m_shapeIndex == constants->PIECE_I) {

        // Special rotation R
        int index = m_currentBlock->m_rotation;

        if(tryRotateCurrentBlock()) return true;

        for(int i = 0; i < 4; i++) {

            int x, y;
            x = constants->WALLKICK_I_R[index][i][0];
            y = constants->WALLKICK_I_R[index][i][1];

            // SDL_Log("trying rotation %d : (%d, %d)", i, x, y);

            m_currentBlock->m_x += x;
            m_currentBlock->m_y += y;

            if (tryRotateCurrentBlock()) return true;

            m_currentBlock->m_x -= x;
            m_currentBlock->m_y -= y;

        }

        return false;


    } else {

        // Classic rotation R
        int index = m_currentBlock->m_rotation;

        if(tryRotateCurrentBlock()) return true;

        for(int i = 0; i < 4; i++) {

            int x, y;
            x = constants->WALLKICK_NORMAL_R[index][i][0];
            y = constants->WALLKICK_NORMAL_R[index][i][1];

            // SDL_Log("trying rotation %d : (%d, %d)", i, x, y);

            m_currentBlock->m_x += x;
            m_currentBlock->m_y += y;

            if (tryRotateCurrentBlock()) return true;

            m_currentBlock->m_x -= x;
            m_currentBlock->m_y -= y;

        }

        return false;

    }

}

bool Tetris::tryRotateCurrentBlock() {

    m_currentBlock->rotate();

    bool wellPlaced = true;

    int actualBottom = m_currentBlock->m_y + m_currentBlock->m_trueBottom;
    int actualLeft = m_currentBlock->m_x + m_currentBlock->m_trueLeft;
    int actualRight = m_currentBlock->m_x + m_currentBlock->m_trueRight;

    if(
        actualBottom >= heightCells ||
        actualLeft < 0 ||
        actualRight >= widthCells
    ) {
        wellPlaced = false;
    } else { // Test that the piece is not overlapping any other piece

        for(Block* loopCurBlock : m_blocks) {
            if(m_currentBlock->doesOverlap(*loopCurBlock)) {
                wellPlaced = false;
                break;
            }
        }

    }

    if(wellPlaced) {
        lastDownMove = SDL_GetTicks();
    } else {
        m_currentBlock->rotateBack();
        return false;
    }

    return true;

}

// Return the whether the piece has been able to move
bool Tetris::moveCurrentBlockDown() {

    // Move the block
    m_currentBlock->m_y++;

    bool wellPlaced = true;

    int actualBottom = m_currentBlock->m_y + m_currentBlock->m_trueBottom;

    if( actualBottom >= heightCells ) {
        wellPlaced = false;
    } else { // Test that the piece is not overlapping anypiece

        for(Block* loopCurBlock : m_blocks) {
            if(m_currentBlock->doesOverlap(*loopCurBlock)) {
                wellPlaced = false;
                break;
            }
        }

    }

    if(wellPlaced) {
        lastDownMove = SDL_GetTicks();
    } else {
        m_currentBlock->m_y--;
        return false;
    }

    return true;

}

// Return the whether the piece has been able to move
bool Tetris::moveCurrentBlockSide() {

    int originalX = m_currentBlock->m_x;

    if(leftArrowPressed) {
        m_currentBlock->m_x --;
    } else if(rightArrowPressed) {
        m_currentBlock->m_x ++;
    } else {
        return true;
    }

    bool wellPlaced = true;

    int actualLeft = m_currentBlock->m_x + m_currentBlock->m_trueLeft;
    int actualRight = m_currentBlock->m_x + m_currentBlock->m_trueRight;

    if(
        actualLeft < 0 ||
        actualRight >= widthCells
    ) {
        wellPlaced = false;
    } else { // Test that the piece is not overlapping anypiece

        for(Block* loopCurBlock : m_blocks) {
            if(m_currentBlock->doesOverlap(*loopCurBlock)) {
                wellPlaced = false;
                break;
            }
        }

    }

    if(wellPlaced) {
        lastMove = SDL_GetTicks();
    } else {
        // Move the block back
        m_currentBlock->m_x = originalX;
        return false;
    }

    return true;

}

void Tetris::handleInput(const SDL_Event &event) {
    switch (event.type) {

        case SDL_KEYDOWN:
            if (event.key.repeat == 0) {
                switch (event.key.keysym.sym) {

                    case SDLK_SPACE:
                        spaceBarPressed = true;
                        break;

                    case SDLK_LEFT:
                        leftArrowPressed = true;
                        break;

                    case SDLK_RIGHT:
                        rightArrowPressed = true;
                        break;

                    case SDLK_DOWN:
                        bottomArrowPressed = true;
                        break;

                    case SDLK_f:
                        displayFaces = (!displayFaces); // Switch the display faces
                        break;

                    default:
                        break;
                }
            }
            break;

        case SDL_KEYUP:
            if (event.key.repeat == 0) {
                switch (event.key.keysym.sym) {

                case SDLK_SPACE:
                    // spaceBarPressed = false;
                    break;

                case SDLK_LEFT:
                        leftArrowPressed = false;
                        break;

                case SDLK_RIGHT:
                    rightArrowPressed = false;
                    break;

                case SDLK_DOWN:
                    bottomArrowPressed = false;
                    break;

                default:
                    break;
                }
            }
            break;

        default:
            break;
    }
}
