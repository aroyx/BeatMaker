#pragma once

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

struct GlobalData
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool quit;
};

bool init_state();

extern struct GlobalData global;

