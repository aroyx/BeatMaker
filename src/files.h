#pragma once

void add_file(const char *file_path);
const char **get_file_names(int *total_files);
void remove_file_at(int index);
bool file_already_added(const char *file_path);
void cleanup_files();
