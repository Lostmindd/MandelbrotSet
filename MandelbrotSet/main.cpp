#include <iostream>

#include <Windows.h>
#include <SDL.h>

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

SDL_Window* window = nullptr;

SDL_Renderer* renderer = nullptr;


// Инициализирует окно и рендерер
bool init()
{
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Can't init SDL: " << SDL_GetError() << std::endl;
        ok = false;
    }

    window = SDL_CreateWindow("Примитивы", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "Can't create window: " << SDL_GetError() << std::endl;
        ok = false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "Can't create renderer: " << SDL_GetError() << std::endl;
        ok = false;
    }

    return ok;
}

bool isBelongToSet(float x, float y, float z1, float z2, unsigned step)
{
    if (step >= 50)
        return true;
    float new_z1 = (z1 * z1 - z2 * z2) + x;
    float new_z2 = (2 * z1 * z2) + y;

    if ((new_z1 * new_z1 + new_z2 * new_z2) > 4)
        return false;
    isBelongToSet(x, y, new_z1, new_z2,  ++step);
}

int main(int argc, char* argv[])
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);

    SDL_Init(SDL_INIT_EVERYTHING);

    init();

    SDL_Event window_event;


    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

    const float x_diff = 3.0 / SCREEN_WIDTH;
    const float y_diff = 2.0 / SCREEN_HEIGHT;
    float x = -2;
    float y = -1;
    for (short i = 0; i < SCREEN_HEIGHT; i++)
    {
        x = -2;
        for (short j = 0; j < SCREEN_WIDTH; j++)
        {
            SDL_SetRenderDrawColor(renderer, 255.0/ SCREEN_WIDTH * j, 255.0 / SCREEN_WIDTH * j, 255.0 / SCREEN_WIDTH * j, 0);
            if (isBelongToSet(x, y, 0, 0, 0))
            {
                SDL_RenderDrawPoint(renderer, j, i);
            }
            x += x_diff;
        }
        y += y_diff;
    }




    SDL_RenderPresent(renderer);
    while (true)
    {
        if (SDL_PollEvent(&window_event))
        {
            if (SDL_QUIT == window_event.type)
            {
                break;
            }
        }
    }



    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return EXIT_SUCCESS;
}