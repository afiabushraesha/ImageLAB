#include "include/file_dialog.hpp"
#include "../vendor/include/imgui/imgui.h"

#include <cstdio>
#include <vector>
#include <string>
#include <dirent.h>

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

static std::vector<std::string> listDir(const char *in_dir, app::ListDirMode mode) {
    DIR *dir = NULL;
    dirent *dir_entry = NULL;
    
    dir = opendir(in_dir);

    if (dir == NULL) return std::vector<std::string>(0);

    std::vector<std::string> out;
    size_t k = 0;

    while ((dir_entry = readdir(dir)) != NULL) {
        if (dir_entry->d_name[0] == '.') {
            continue;
        }
        if ((mode == app::ListDirMode::File && dir_entry->d_type == DT_REG) ||
            (mode == app::ListDirMode::Folder && dir_entry->d_type == DT_DIR)) {
            out.push_back(dir_entry->d_name);
        }
        else if (mode == app::ListDirMode::FileAndFolder) {
            out.push_back(dir_entry->d_name);
        }
    }

    closedir(dir);
    return out;
}

void app::FolderContentDialog::begin(ListBoxState *state, const char *window_title,
                                     const std::string &base_path, ListDirMode mode) {
    m_mode = mode;

    if (m_crnt_dir.empty()) {
        m_crnt_dir = base_path;
    }

    if(!ImGui::Begin(window_title, &m_show_window)) {
        return;
    }

    if (ImGui::Button("<")) {
        removeLastPath(m_crnt_dir);
    }

    ImGui::SameLine();
    ImGui::Text("Folder: %s", m_crnt_dir.c_str());
    ImGui::Separator();

    if (!ImGui::BeginListBox("##1", {-1.0f, 0.0f})) {
        ImGui::End();
        return;
    }
    
    m_item_list = listDir(m_crnt_dir.c_str(), mode);
    for (int i = 0; i < m_item_list.size(); i++) {
        state->selected = (state->selected_idx == i);

        if (ImGui::Selectable(m_item_list[i].c_str(), state->selected)) {
            state->old_selected_idx = state->selected_idx;
            state->selected_idx = i;
        }

        if (state->selected) {
            ImGui::SetItemDefaultFocus();
        }

        if (state->selected && state->selected_idx == state->old_selected_idx) {
            appendPath(m_crnt_dir, m_item_list[i]);

            if (stat(m_crnt_dir.c_str(), &m_item_stat) != 0) {
                m_show_window = false;
                break;
            }

            if (m_item_stat.st_mode & S_IFDIR) {
                state->reset();
            } else {
                m_show_window = false;
                m_path = m_crnt_dir;
            }
        }
    }
    ImGui::EndListBox();
}

void app::FolderContentDialog::end(ListBoxState *state) {
    if (ImGui::Button("Ok")) {
        if (state->selected_idx < 0) {
            m_show_window = false;
        } else {
            appendPath(m_crnt_dir, m_item_list[state->selected_idx]);

            if (stat(m_crnt_dir.c_str(), &m_item_stat) != 0) {
                m_show_window = false;
            } else if ((m_item_stat.st_mode & S_IFDIR) && m_mode == ListDirMode::FileAndFolder) {
                state->reset();
            } else if ((m_item_stat.st_mode & S_IFDIR) && m_mode == ListDirMode::Folder) {
                state->reset();
                m_show_window = false;
            } else {
                m_show_window = false;
                m_path = m_crnt_dir;
            }
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel")) {
        m_show_window = false;
    }

    ImGui::End();
}

void app::dialogRenderImageImport(FolderContentDialog *dialog, ListBoxState *state,
                                  const std::string &base_path, const char *desc) {
    dialog->begin(state, "File > Open", base_path, ListDirMode::FileAndFolder);
    ImGui::TextWrapped("%s", desc);
    dialog->end(state);
}

void app::ListBoxState::reset() {
    selected_idx = -1;
    old_selected_idx = 0;
    selected = false;
}
