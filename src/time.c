#include "time.h"
#include "SDL3/SDL_timer.h"

float fps       = 2000;
float frametime = 0.5;

float last_tick = 0;

void start_frame_track_time()
{
    last_tick = (float)SDL_GetTicksNS();
}

void end_frame_track_time()
{
    float nframetime = ((float)SDL_GetTicksNS() - last_tick) / 1e6;
    float nfps       = 1000.0 / frametime;

    fps       = fps + ((nfps - fps) / 60.0);
    frametime = frametime + (nframetime - frametime) / 60;
}

float get_fps()
{
    return fps;
}

float get_frametime()
{
    return frametime;
}
