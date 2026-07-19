#include <stdbool.h>
#include <stdio.h>
#include <SDL3/SDL.h>

#include "../brand/var.h"
#include "features.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int WebWidth = 800;
int WebHeight = 600;
int WindowWidth = 800;
int WindowHeight = 636;

SDL_FRect urlBar;
SDL_FRect urlBottom;

void resizeWindow(int newWidth, int newHeight)
{
    WindowWidth = newWidth;
    WindowHeight = newHeight;

    urlBar.x = 0.0f;
    urlBar.y = 0.0f;
    urlBar.w = (float)newWidth;
    urlBar.h = 35;

    urlBottom.x = 0.0f;
    urlBottom.y = 35.0f;
    urlBottom.w = (float)newWidth;
    urlBottom.h = 1;
}

int main(int argc, char *argv[])
{
    char *url = features(argc, argv);

    char title[512];
    snprintf(title, sizeof(title), "Katzi-Browser - %s", url);

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    if (!SDL_CreateWindowAndRenderer(
            title,
            WindowWidth,
            WindowHeight,
            SDL_WINDOW_RESIZABLE,
            &window,
            &renderer))
    {
        SDL_Log("SDL_CreateWindowAndRenderer failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    resizeWindow(WindowWidth, WindowHeight);

    bool running = true;
    bool urlbarselected = false;

    while (running)
    {
        SDL_Event e;

        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;

                case SDL_EVENT_WINDOW_RESIZED:
                    resizeWindow(e.window.data1, e.window.data2);
                    break;

                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        SDL_Log("Left mouse button pressed at (%f, %f)",
                        e.button.x,
                        e.button.y);
                        if(e.button.y < 35){
                            urlbarselected = true;
                        }else{
                            urlbarselected = false;
                        }
                    }
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        if(urlbarselected){
            SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        }else{
            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        }
        
        SDL_RenderFillRect(renderer, &urlBar);

        SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
        SDL_RenderFillRect(renderer, &urlBottom);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
