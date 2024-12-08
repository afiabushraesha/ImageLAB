#include "include/dialog.hpp"
#include "include/path.hpp"

#include "../vendor/include/imgui/imgui.h"

#include <cstdio>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>

static std::vector<std::string> listDir(const char *in_dir, app::ListDirMode mode) {
    DIR *dir = NULL;
    dirent *dir_entry = NULL;
    
    dir = opendir(in_dir);

    if (dir == NULL) return std::vector<std::string>(0);

    std::vector<std::string> out;
    size_t k = 0;

    struct stat item_stat;
    std::string full_path = in_dir;

    while ((dir_entry = readdir(dir)) != NULL) {
        if (dir_entry->d_name[0] == '.') {
            continue;
        }

        app::pathAppend(&full_path, dir_entry->d_name);
        stat(full_path.c_str(), &item_stat);

        if ((mode == app::ListDirMode::File && S_ISREG(item_stat.st_mode)) ||
            (mode == app::ListDirMode::Folder && S_ISDIR(item_stat.st_mode))) {
            out.push_back(dir_entry->d_name);
        }
        else if (mode == app::ListDirMode::FileAndFolder) {
            out.push_back(dir_entry->d_name);
        }

        full_path = in_dir;
    }

    closedir(dir);
    return out;
}

bool app::FolderContentDialog::begin(ListBoxState *state, const char *window_title,
                                     const std::string &base_path, ListDirMode mode) {
    m_mode = mode;

    if (m_crnt_dir.empty()) {
        m_crnt_dir = base_path;
    }

    if(!ImGui::Begin(window_title, &m_show_window)) {
        return true;
    }

    if (ImGui::Button("<")) {
        pathRemoveLast(m_crnt_dir);
    }

    ImGui::SameLine();
    ImGui::Text("Folder: %s", m_crnt_dir.c_str());
    ImGui::Separator();

    if (!ImGui::BeginListBox("##1", {-1.0f, 0.0f})) {
        ImGui::End();
        return true;
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
            pathAppend(&m_crnt_dir, m_item_list[i]);

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
    
    return false;
}

void app::FolderContentDialog::end(ListBoxState *state, bool error) {
    if (error) {
        return;
    }

    if (ImGui::Button("Ok")) {
        if (state->selected_idx < 0) {
            state->reset();
            if (m_mode == ListDirMode::Folder) {
                m_path = m_crnt_dir;
            }
            m_show_window = false;
        } else {
            state->reset();

            if (stat(m_crnt_dir.c_str(), &m_item_stat) != 0) {
                m_show_window = false;
            } else if ((m_item_stat.st_mode & S_IFDIR) && m_mode == ListDirMode::Folder) {
                m_path = m_crnt_dir;
                m_show_window = false;
            } else if (m_item_stat.st_mode & S_IFREG) {
                pathAppend(&m_crnt_dir, m_item_list[state->selected_idx]);
                m_path = m_crnt_dir;
                m_show_window = false;
            } else { // it can only be a folder now
                pathAppend(&m_crnt_dir, m_item_list[state->selected_idx]);
            }
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel")) {
        state->reset();
        m_show_window = false;
    }

    ImGui::End();
}

void app::dialogRenderImageImport(FolderContentDialog *dialog, ListBoxState *state,
                                  const std::string &base_path, const char *desc) {
    bool error = dialog->begin(state, "File > Open", base_path, ListDirMode::FileAndFolder);
    ImGui::TextWrapped("Description: %s", desc);
    dialog->end(state, error);
}

void app::dialogRenderImageExport(FolderContentDialog *dialog, ListBoxState *state,
                                  char *file_name_buf, size_t file_name_buf_size,
                                  const std::string &base_path, const char *desc) {
    bool error = dialog->begin(state, "File > Export", base_path, ListDirMode::Folder);
    ImGui::InputText("File name\n", file_name_buf, file_name_buf_size);
    ImGui::TextWrapped("Description: %s", desc);
    dialog->end(state, error);
}

void app::ListBoxState::reset() {
    selected_idx = -1;
    old_selected_idx = 0;
    selected = false;
}
