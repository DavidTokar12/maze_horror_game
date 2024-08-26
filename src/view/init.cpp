#include <SDL.h>

class GameView
{
private:
    SDL_Window *window = nullptr;
    SDL_Surface *windowSurface = nullptr;

public:
    GameView();
    size_t render();
}