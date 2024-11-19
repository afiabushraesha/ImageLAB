#include "include/file_dialog.hpp"
#include "../vendor/include/imgui/imgui.h"

#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
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

static bool checkIfPathImage(const std::string &s) {
    std::string type = s.substr(s.size() - 5, 5);
    if (type == ".jpeg") return true;

    type = s.substr(s.size() - 4, 4);

    if (type == ".jpg" || type == ".png" ||
        type == ".bmp" || type == ".tga") {
        return true;
    }

    return false;
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
                           std::string &base_path, const char *desc) {
    if(!ImGui::Begin("File > Open", &show_window)) {
        return;
    }

    if (ImGui::Button("<")) {
        removeLastPath(base_path);
    }

    ImGui::SameLine();
    ImGui::Text("Folder: %s", base_path.c_str());
    ImGui::Separator();

    if (!ImGui::BeginListBox("##1", {-1.0f, 0.0f})) {
        ImGui::End();
        return;
    }
    
    std::vector<std::string> vec = listDir(base_path.c_str());
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
            appendPath(base_path, vec[i]);

            if (stat(base_path.c_str(), &selected_stat) != 0) {
                show_window = false;
                break;
            }

            if (selected_stat.st_mode & S_IFDIR) {
                state->selected_idx = -1;
                state->old_selected_idx = 0;
                state->selected = false;
            }
            else {
                show_window = false;
                file_path = base_path;
            }
        }
    }
    ImGui::EndListBox();

    ImGui::TextWrapped("Description:\n%s", desc);

    if (ImGui::Button("Ok")) {
        if (state->selected_idx < 0) {
            show_window = false;
        } else {
            appendPath(base_path, vec[state->selected_idx]);

            if (stat(base_path.c_str(), &selected_stat) != 0) {
                show_window = false;
            }
            else if (!(selected_stat.st_mode & S_IFDIR)) {
                show_window = false;
                file_path = base_path;
            }
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel")) {
        show_window = false;
    }

    ImGui::End();
}
