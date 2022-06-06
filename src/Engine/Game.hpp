/**
 * Header file for Game class.
 * @file Game.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef GAME_H
#define GAME_H

#include <random>

#include <SDL2/SDL.h>

/** A boilerplate Game class made for inheritance */

class Game {
    protected:

        SDL_Window* window;
        SDL_Renderer* m_renderer;
        SDL_Event event;

        bool quit;
        bool ready;

        int gameWindowWidth;
        int gameWindowHeight;
        int gameFrameRate;

        int timePerFrame;
        int lastTime;
        int timeElapsed;
        int timeToWait;

        std::random_device dev;
        std::mt19937 m_randomRange;
        std::uniform_int_distribution<int> dist;

        void setupSDL();
        void destroySDL();
        void mainLoop();
        virtual void update();
        void gameLog(const char[] = nullptr);
        void recordInput();
        virtual void handleInput(const SDL_Event&);

    public:
        Game(int = 0, int = 0, int = 30);
        void setup();
        void start();
        void stop();
        void destroy();
        void drawTexture(SDL_Texture* = nullptr, const SDL_Rect* = nullptr, const SDL_Rect* = nullptr, const double = 0, const SDL_Point* = nullptr, const SDL_RendererFlip = SDL_FLIP_NONE);
};

#endif // GAME_H