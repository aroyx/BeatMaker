#include <stdlib.h>
#include <SDL3/SDL.h>

#include <cimgui.h>
#include <cimgui_impl.h>

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

        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        igNewFrame();

        igShowDemoWindow(nullptr);

        igRender();
        ImDrawData* draw_data = igGetDrawData();
        const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
        ImGui_ImplSDLRenderer3_RenderDrawData(draw_data, global.renderer);
        SDL_RenderPresent(global.renderer);
    }

    quit();
    return EXIT_SUCCESS;
}
