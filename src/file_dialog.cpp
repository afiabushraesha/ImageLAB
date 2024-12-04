#include "include/file_dialog.hpp"
#include "../vendor/include/imgui/imgui.h"

#include <cstdio>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>

static void appendPath(std::string &s, const std::string &appendix) {
    if (s.back() != '/') s.push_back('/');
    s.append(appendix);
}

static void removeLastPath(std::string &s) {
    size_t i = s.size() - 1;
    while (s[i] != '/') i--;

    if (i == 0) return;
    s.resize(s.size() - (s.size() - i));
}

static std::vector<std::string> listDir(const char *in_dir) {
    DIR *dir = NULL;
    dirent *dir_entry = NULL;
    
    dir = opendir(in_dir);

    if (dir == NULL) return std::vector<std::string>(0);

    std::vector<std::string> out;
    size_t k = 0;

    while ((dir_entry = readdir(dir)) != NULL) {
        if (dir_entry->d_name[0] == '.') continue;
        out.push_back(dir_entry->d_name);
    }

    closedir(dir);
    return out;
}


void app::FileDialog::show(ListBoxState *state,
                           const std::string &base_path, const char *desc) {
    if (crnt_dir.empty()) {
        crnt_dir = base_path;
    }

    if(!ImGui::Begin("File > Open", &show_window)) {
        return;
    }

    if (ImGui::Button("<")) {
        removeLastPath(crnt_dir);
    }

    ImGui::SameLine();
    ImGui::Text("Folder: %s", crnt_dir.c_str());
    ImGui::Separator();

    if (!ImGui::BeginListBox("##1", {-1.0f, 0.0f})) {
        ImGui::End();
        return;
    }
    
    std::vector<std::string> vec = listDir(crnt_dir.c_str());
    struct stat selected_stat;
    for (int i = 0; i < vec.size(); i++) {
        state->selected = (state->selected_idx == i);

        if (ImGui::Selectable(vec[i].c_str(), state->selected)) {
            state->old_selected_idx = state->selected_idx;
            state->selected_idx = i;
        }

        if (state->selected) {
            ImGui::SetItemDefaultFocus();
        }

        if (state->selected && state->selected_idx == state->old_selected_idx) {
            appendPath(crnt_dir, vec[i]);

            if (stat(crnt_dir.c_str(), &selected_stat) != 0) {
                show_window = false;
                break;
            }

            if (selected_stat.st_mode & S_IFDIR) {
                state->reset();
            } else {
                show_window = false;
                file_path = crnt_dir;
            }
        }
    }
    ImGui::EndListBox();

    ImGui::TextWrapped("Description:\n%s", desc);

    if (ImGui::Button("Ok")) {
        if (state->selected_idx < 0) {
            show_window = false;
        } else {
            appendPath(crnt_dir, vec[state->selected_idx]);

            if (stat(crnt_dir.c_str(), &selected_stat) != 0) {
                show_window = false;
            } else if (selected_stat.st_mode & S_IFDIR) {
                state->reset();
            } else {
                show_window = false;
                file_path = crnt_dir;
            }
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel")) {
        show_window = false;
    }

    ImGui::End();
}

void app::ListBoxState::reset() {
    selected_idx = -1;
    old_selected_idx = 0;
    selected = false;
}
