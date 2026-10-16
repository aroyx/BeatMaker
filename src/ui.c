#include "ui.h"
#include "SDL3/SDL_dialog.h"
#include "SDL3/SDL_log.h"
#include "files.h"
#include "global.h"
#include "time.h"

#include <cimgui.h>
#include <cimgui_impl.h>

void ui_prepare_draw()
{
    ImGui_ImplSDL3_NewFrame();
    ImGui_ImplSDLRenderer3_NewFrame();
    igNewFrame();

    ImGuiID main_id = igDockSpaceOverViewport(0, NULL, 0, NULL);

    static bool first_time = true;

    if (first_time)
    {
        first_time = false;

        igDockBuilderRemoveNode(main_id);
        igDockBuilderAddNode(main_id, 0);
        igDockBuilderSetNodeSize(main_id, igGetMainViewport()->Size);

        ImGuiID dockIdLeft =
            igDockBuilderSplitNode(main_id, ImGuiDir_Left, 0.25, nullptr, &main_id);

        ImGuiID dockIdRight =
            igDockBuilderSplitNode(main_id, ImGuiDir_Right, 0.25, nullptr, &main_id);

        igDockBuilderDockWindow("###Left", dockIdLeft);
        igDockBuilderDockWindow("###Right", dockIdRight);
        igDockBuilderDockWindow("###Center", main_id);
    }
}

static void SDLCALL file_callback(void *userdata, const char *const *filelist, int filter)
{
    if (!filelist)
    {
        SDL_Log("An error occured: %s", SDL_GetError());
        return;
    }

    while (*filelist)
    {
        add_file(*filelist);
        filelist++;
    }
}

const SDL_DialogFileFilter audio_filters[] = {
    //
    {"All audio", "wav;mp3;ogg;flac;aac;m4a"},
    {"All files", "*"}  //
};

void draw_loaded_files()
{
    int total_files    = 0;
    const char **names = get_file_names(&total_files);

    for (int i = total_files - 1; i >= 0; i--)
    {
        if (igButton(names[i], (ImVec2_c) {})) {
            remove_file_at(i);
        }
    }
}

void ui_draw()
{
    if (igBegin("Options###Left", nullptr, 0))
    {
        if (igButton("Select File", (ImVec2) {}))
        {
            SDL_ShowOpenFileDialog(file_callback, NULL, global.window, audio_filters,
                                   SDL_arraysize(audio_filters), NULL, true);
        }

        draw_loaded_files();

        // draw these in teh bottom
        igSetCursorPosY(igGetWindowHeight() - 50);
        igSeparatorText("Misc");
        igTextWrapped("FrameTime: %.3fms", get_frametime());
    }
    igEnd();

    if (igBegin("Central Screen###Center", nullptr, 0)) {}
    igEnd();

    // if (igBegin("Extra Options###Right", nullptr, 0)) {}
    // igEnd();
}
