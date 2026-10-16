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

    static int selected_index = -1;

    ImGuiTableFlags table_flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner;

    if (igBeginTable("PlaylistTable", 2, table_flags, (ImVec2) {0, 0}, 0))
    {
        igTableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch, 0.0f, 0);
        igTableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 0.0f, 0);

        for (int i = 0; i < total_files; i++)
        {
            igTableNextRow(0, 0);
            igPushID_Int(i);

            // Column 1: Name
            igTableSetColumnIndex(0);

            bool is_selected = (selected_index == i);

            if (igSelectable_Bool(names[i], is_selected, ImGuiSelectableFlags_SpanAvailWidth, (ImVec2) {0, 0}))
            {
                selected_index = i;
            }

            if (igBeginPopupContextItem("TrackContextMenu", ImGuiPopupFlags_MouseButtonRight))
            {
                if (igMenuItem_Bool("Add To Editor", NULL, false, true)) {}
                igSeparator();
                if (igMenuItem_Bool("Remove", NULL, false, true))
                {
                    remove_file_at(i);
                    igEndPopup();
                    igPopID();
                    break;
                }
                igEndPopup();
            }

            // Column 2: X
            igTableSetColumnIndex(1);

            if (igSmallButton("X"))
            {
                remove_file_at(i);

                if (selected_index == i) selected_index = -1;

                igPopID();
                break;
            }

            igPopID();
        }
        igEndTable();
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

        igSeparatorText("Misc");
        igTextWrapped("FrameTime: %.3fms", get_frametime());
    }
    igEnd();

    if (igBegin("Central Screen###Center", nullptr, 0)) {}
    igEnd();

    // if (igBegin("Extra Options###Right", nullptr, 0)) {}
    // igEnd();
}
