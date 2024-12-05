#ifndef _APP_DIR_WINDOW_H_
#define _APP_DIR_WINDOW_H_

#include <string>
#include <vector>
#include <sys/stat.h>

namespace app {
    struct ListBoxState {
        bool selected = false;
        int selected_idx = -1;
        int old_selected_idx = 0;

        void reset();
    };

    enum class ListDirMode : unsigned char {
        FileAndFolder,
        Folder,
        File
    };

    struct FolderContentDialog {
        std::string m_path;
        std::string m_crnt_dir;
        std::vector<std::string> m_item_list;
        struct stat m_item_stat;
        ListDirMode m_mode;
        bool m_show_window = false;

        bool begin(ListBoxState *state, const char *window_title,
                   const std::string &base_path, ListDirMode mode);
        void end(ListBoxState *state, bool error);
    };

    void dialogRenderImageImport(FolderContentDialog *dialog, ListBoxState *state,
                                 const std::string &base_path, const char *desc);
    void dialogRenderImageExport(FolderContentDialog *dialog, ListBoxState *state,
                                 char *file_name_buf, size_t file_name_buf_size,
                                 const std::string &base_path, const char *desc);
}

#endif
