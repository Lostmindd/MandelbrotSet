#include <iostream>

#include <SDL.h>

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if (!window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Event window_event;
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
    SDL_Quit();

    return EXIT_SUCCESS;
}