#include <stdlib.h>
#include <SDL3/SDL.h>

#include "global.h"
#include "window/window.h"

bool init()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialise SDL!\nSDL_Error: %s",
                     SDL_GetError());
        return false;
    }
    if (!init_state()) return false;
    if (!init_window()) return false;
    return true;
}

void quit()
{
    quit_window();
    SDL_Quit();
}

int main()
{
    if (!init()) { return EXIT_FAILURE; }

    while (!global.quit)
    {
        poll_events();

        SDL_SetRenderDrawColor(global.renderer, 10, 160, 230, 255);
        SDL_RenderClear(global.renderer);


        SDL_RenderPresent(global.renderer);
    }

    quit();
    return EXIT_SUCCESS;
}
