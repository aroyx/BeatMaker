#include <SDL3/SDL.h>

#include "window.h"
#include "../global.h"

bool init_window()
{
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");

    global.window = SDL_CreateWindow("BeatMaker", 1200, 680,  //
                                     SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!global.window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Unable to create Window!\nSDL_Error: %s",
                     SDL_GetError());
        return false;
    }

    global.renderer = SDL_CreateRenderer(global.window, nullptr);
    if (!global.renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Unable to create Renderer!\nSDL_Error: %s",
                     SDL_GetError());
        return false;
    }

    SDL_SetRenderVSync(global.renderer, 1);

    return true;
}

void quit_window()
{
    SDL_DestroyRenderer(global.renderer);
    SDL_DestroyWindow(global.window);
    global.window = nullptr;
}

SDL_Event event;

void poll_events()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT) { global.quit = true; }
    }
}
