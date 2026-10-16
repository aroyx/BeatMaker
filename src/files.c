#include "files.h"
#include "SDL3/SDL_log.h"

#include <SDL3/SDL_filesystem.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 50

struct Files
{
    const char *file_paths[MAX_FILES];
    const char *names[MAX_FILES];
};

struct Files files;
int current_files = 0;

void add_file(const char *file_path)
{
    if (!SDL_GetPathInfo(file_path, NULL))
    {
        SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Unable to Find file: %s", file_path);
        return;
    }
    if (file_already_added(file_path))
    {
        SDL_Log("File already added! Path: %s", file_path);
        return;
    }

    if (current_files == MAX_FILES)
    {
        free((void *)files.file_paths[0]);

        memmove(&files.file_paths[0], &files.file_paths[1],
                (MAX_FILES - 1) * sizeof(files.file_paths[0]));
        memmove(&files.names[0], &files.names[1], (MAX_FILES - 1) * sizeof(files.names[0]));

        current_files--;
    }

    char *path                      = strdup(file_path);
    files.file_paths[current_files] = path;

    const char *last_slash = strrchr(path, '/');

    if (!last_slash) last_slash = strrchr(path, '\\');

    if (last_slash != NULL) { files.names[current_files] = last_slash + 1; }
    else { files.names[current_files] = path; }

    SDL_Log("File Added: %s", file_path);

    current_files++;
}

void remove_file_at(int index)
{
    if (index < 0 || index >= current_files) { return; }

    free((void *)files.file_paths[index]);

    if (index < current_files - 1)
    {
        memmove(&files.file_paths[index], &files.file_paths[index + 1],
                (current_files - index - 1) * sizeof(files.file_paths[0]));
        memmove(&files.names[index], &files.names[index + 1],
                (current_files - index - 1) * sizeof(files.names[0]));
    }

    current_files--;

    files.file_paths[current_files] = NULL;
    files.names[current_files]      = NULL;
}

const char **get_file_names(int *total_files)
{
    *total_files = current_files;
    return files.names;
}

bool file_already_added(const char *file_path)
{
    for (int i = 0; i < current_files; i++)
    {
        if (strcmp(files.file_paths[i], file_path) == 0) { return true; }
    }
    return false;
}
