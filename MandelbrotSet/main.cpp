#include <iostream>

#include <Windows.h>
#include <SDL.h>

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

SDL_Window* window = nullptr;

SDL_Renderer* renderer = nullptr;


// Èíèöèàëèçèğóåò îêíî è ğåíäåğåğ
bool init()
{
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Can't init SDL: " << SDL_GetError() << std::endl;
        ok = false;
    }

    window = SDL_CreateWindow("Ïğèìèòèâû", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

Uint8 findÑolorInMandelbrotSet(double x, double y, double z1, double z2, Uint8 step)
{
    if (step >= 100)
        return step * 2.5;
    double new_z1 = (z1 * z1 - z2 * z2) + x;
    double new_z2 = (2 * z1 * z2) + y;

    if ((new_z1 * new_z1 + new_z2 * new_z2) > 4)
        return step * 2.5;
    findÑolorInMandelbrotSet(x, y, new_z1, new_z2, ++step);
}

Uint8 getMandelbrotColor(double x, double y)
{
    return findÑolorInMandelbrotSet(x, y, 0, 0, 0);
}

void clearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
}

void generateMandelbrotSet(double min_x, double max_x, double min_y, double max_y)
{
    const double x_diff = (max_x - min_x) / SCREEN_WIDTH;
    const double y_diff = (max_y - min_y) / SCREEN_HEIGHT;
    double x = min_x;
    double y = min_y;
    for (short i = 0; i < SCREEN_HEIGHT; i++)
    {
        x = min_x;
        for (short j = 0; j < SCREEN_WIDTH; j++)
        {
            Uint8 color = getMandelbrotColor(x, y);
            SDL_SetRenderDrawColor(renderer, (color * 5) % 256, (color * 7) % 256, (color * 11) % 256, 255);
            SDL_RenderDrawPoint(renderer, j, i);
            x += x_diff;
        }
        y += y_diff;
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    SDL_Init(SDL_INIT_EVERYTHING);

    init();

    SDL_Event window_event;

    double curent_min_x = -1;
    double curent_max_x = 1;
    double curent_min_y = -1;
    double curent_max_y = 1;
    double curent_scroll_step = (curent_max_x - curent_min_x) / 10;

    clearScreen();
    generateMandelbrotSet(curent_min_x, curent_max_x, curent_min_y, curent_max_y);

    while (true)
    {
        if (SDL_PollEvent(&window_event))
        {
            if (SDL_MOUSEWHEEL == window_event.type)
            {
                if (window_event.wheel.y == -1) 
                {
                    curent_min_x -= curent_scroll_step;
                    curent_max_x += curent_scroll_step;
                    curent_min_y -= curent_scroll_step;
                    curent_max_y += curent_scroll_step;
                }
                else if (window_event.wheel.y == 1) 
                {
                    curent_min_x += curent_scroll_step;
                    curent_max_x -= curent_scroll_step;
                    curent_min_y += curent_scroll_step;
                    curent_max_y -= curent_scroll_step;
                }
                clearScreen();
                generateMandelbrotSet(curent_min_x, curent_max_x, curent_min_y, curent_max_y);
                curent_scroll_step = (curent_max_x - curent_min_x)/10;
            }

            if (SDL_KEYDOWN == window_event.type)
            {
                if (window_event.key.keysym.sym == SDLK_UP) {
                    curent_min_y -= curent_scroll_step;
                    curent_max_y -= curent_scroll_step;
                }
                else if (window_event.key.keysym.sym == SDLK_DOWN) {
                    curent_min_y += curent_scroll_step;
                    curent_max_y += curent_scroll_step;
                }
                else if (window_event.key.keysym.sym == SDLK_LEFT) {
                    curent_min_x -= curent_scroll_step;
                    curent_max_x -= curent_scroll_step;
                }
                else if (window_event.key.keysym.sym == SDLK_RIGHT) {
                    curent_min_x += curent_scroll_step;
                    curent_max_x += curent_scroll_step;
                }
                clearScreen();
                generateMandelbrotSet(curent_min_x, curent_max_x, curent_min_y, curent_max_y);
                curent_scroll_step = (curent_max_x - curent_min_x) / 10;
            }

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