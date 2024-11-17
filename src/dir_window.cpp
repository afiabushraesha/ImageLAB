#include "include/dir_window.hpp"
#include "../vendor/include/imgui/imgui.h"

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
    while (s.back() != '/') s.pop_back();
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


void app::showDirList(DirListResult *result, ListBoxState *state,
                      std::string &base_path, const char *desc) {
    std::vector<std::string> vec = listDir(base_path.c_str());

    ImGui::Begin("File > Open"); {
        if (ImGui::Button("<")) {
            removeLastPath(base_path);
        }
        ImGui::SameLine();
        ImGui::Text("Folder: %s", base_path.c_str());
        ImGui::Separator();

        if (!ImGui::BeginListBox("##", {-1.0f, 0.0f})) return;
        
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

                struct stat selected_stat;
                if (stat(base_path.c_str(), &selected_stat) != 0) {
                    result->show_window = false;
                    return;
                }

                if (selected_stat.st_mode & S_IFDIR) {
                    state->selected_idx = -1;
                    state->old_selected_idx = 0;
                    state->selected = false;
                }
            }
        }

        ImGui::EndListBox();

        ImGui::Text("Description:\n%s", desc);

        ImGui::Button("Ok");
        ImGui::SameLine();
        ImGui::Button("Cancel");
    }
    ImGui::End();
}
