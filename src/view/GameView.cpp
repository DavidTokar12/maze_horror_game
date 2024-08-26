#include "GameView.hpp"
#include "defs.hpp"

GameView::GameView()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        this->logError();
        return;
    }

    this->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        logError();
        return;
    }
}

GameView::~GameView()
{
    if (window != nullptr)
    {
        SDL_DestroyWindow(this->window);
    }
    SDL_Quit();
}

void GameView::render()
{

    windowSurface = SDL_GetWindowSurface(window);

    SDL_Rect rect = {0, 0, 100, 100};
    SDL_FillRect(windowSurface, &rect, SDL_MapRGB(windowSurface->format, WHITE_COLOR, WHITE_COLOR, WHITE_COLOR));
    SDL_UpdateWindowSurface(window);
}

bool GameView::setFPS(double newFPS)
{
    if (newFPS > 0.0)
    {
        this->fps = newFPS;
        this->tickPerFrame = static_cast<Uint32>(1000.0 / this->fps);
        return true;
    }
    std::cout << "Invalid FPS value. FPS must be greater than 0." << std::endl;
    return false;
}

double GameView::getFPS() const
{
    return this->fps;
}

int GameView::mainGameLoop()

{
    bool running = true;

    while (running)
    {
        Uint32 start_time = SDL_GetTicks();

        this->render();

        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
        }

        Uint32 end_time = SDL_GetTicks();
        Uint32 frame_time = end_time - start_time;
        Uint32 wait_time = tickPerFrame > frame_time ? tickPerFrame - frame_time : 0;
        SDL_Delay(wait_time);
    }

    return 0;
};
