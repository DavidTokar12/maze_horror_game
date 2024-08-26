#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SDL.h>
#include "iostream"

class GameView
{
private:
    SDL_Window *window = nullptr;
    SDL_Surface *windowSurface = nullptr;

    double fps = 30.0;
    double tickPerFrame = static_cast<Uint32>(1000.0 / fps);

    void logError()
    {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
    }

public:
    GameView();
    ~GameView();

    void render();

    double getFPS() const;
    bool setFPS(double newFPS);

    bool initialized() { return window != nullptr; }

    int mainGameLoop();
};

#endif // GAMEVIEW_H
