/**
 * Header file for base Tetris class.
 * @file Tetris.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef TETRIS_H
#define TETRIS_H

#include <vector>
#include <random>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine/Geometry.hpp"
#include "Engine/Game.hpp"
#include "Engine/Color.hpp"

#include "Block.hpp"
#include "constants.hpp"

class Tetris : public Game {
    private:

        Block *m_currentBlock;
        Block *m_nextBlock;
        std::vector< Block* > m_blocks;

        std::uniform_int_distribution<int> blockChoice;

        std::vector<int> possibleShapes;

        bool // Keys
            spaceBarPressed,
            leftArrowPressed,
            rightArrowPressed,
            bottomArrowPressed
        ;

        int lastMove, lastDownMove;

        int widthCells;
        int heightCells;

        std::vector<int> tilesPerLines; // The array of number of square per lines, when reaches the max, it's deleted.

        int score;

        std::vector<SDL_Texture*> digitsTextures;
        std::vector<SDL_Texture*> faceTextures;
        SDL_Texture* backgroundTheme;
        SDL_Texture* gameoverOverlay;

        Color backgroundColor;
        int m_boardOffsetX;
        int m_boardOffsetY;

        bool displayFaces;

        Constants* constants;

        void loadBackgroundTextures();
        void loadDigitsTextures();
        void loadFaceTextures();

        void handleInput(const SDL_Event&);

        bool moveCurrentBlockDown();
        bool moveCurrentBlockSide();
        bool rotateCurrentBlock();
        bool tryRotateCurrentBlock();

        Block* newBlock();

        void display();

        void gameover();

    public:
        Tetris(int = 0, int = 0, int = 30, int = 1, int = 0, int = 0, Constants* = nullptr);
        void setup();
        void update();
        void replay();
};

#endif // TETRIS_H