#include <SDL3/SDL.h>

#include <cimgui.h>
#include <cimgui_impl.h>

#include "window.h"
#include "../global.h"

bool init_window()
{
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");

    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    global.window    = SDL_CreateWindow("BeatMaker", 1200 * main_scale, 680 * main_scale,  //
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

    // Setup Dear ImGui context
    igCreateContext(NULL);
    ImGuiIO *io = igGetIO_Nil();
    (void)io;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    igStyleColorsDark(NULL);

    ImGuiStyle *style = igGetStyle();
    ImGuiStyle_ScaleAllSizes(style, main_scale);
    style->FontScaleDpi         = main_scale;
    style->FrameRounding = 3;
    style->WindowRounding = 8;
    style->PopupRounding = 8;
    style->GrabRounding = 8;
    style->MenuItemRounding = 8;
    style->ScrollbarSize = 10;
    style->ScrollbarRounding = 10;
    style->ScrollbarPadding = 2;

    io->ConfigDpiScaleFonts     = true;
    io->ConfigDpiScaleViewports = true;

    ImGui_ImplSDL3_InitForSDLRenderer(global.window, global.renderer);
    ImGui_ImplSDLRenderer3_Init(global.renderer);
    return true;
}

void quit_window()
{
    ImGui_ImplSDL3_Shutdown();
    ImGui_ImplSDLRenderer3_Shutdown();
    igDestroyContext(NULL);

    SDL_DestroyRenderer(global.renderer);
    SDL_DestroyWindow(global.window);
    global.window = nullptr;
}

SDL_Event event;

void poll_events()
{
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);
        if (event.type == SDL_EVENT_QUIT) { global.quit = true; }
    }
}
