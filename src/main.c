#include <stdlib.h>
#include <SDL3/SDL.h>

#include <cimgui.h>
#include <cimgui_impl.h>

#include "global.h"
#include "time.h"
#include "ui.h"
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

void prepare_draw()
{
    SDL_SetRenderDrawColor(global.renderer, 10, 160, 230, 255);
    SDL_RenderClear(global.renderer);

    ui_prepare_draw();
}

void draw()
{
    igRender();
    ImDrawData *draw_data = igGetDrawData();
    const bool is_minimized =
        (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
    ImGui_ImplSDLRenderer3_RenderDrawData(draw_data, global.renderer);

    end_frame_track_time();

    SDL_RenderPresent(global.renderer);
}

int main()
{
    if (!init()) { return EXIT_FAILURE; }

    while (!global.quit)
    {
        start_frame_track_time();
        poll_events();
        prepare_draw();

        ui_draw();

        draw();
    }

    quit();
    return EXIT_SUCCESS;
}
