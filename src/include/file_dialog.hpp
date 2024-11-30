#ifndef _APP_DIR_WINDOW_H_
#define _APP_DIR_WINDOW_H_

#include <string>

namespace app {
    struct ListBoxState {
        bool selected = false;
        int selected_idx = -1;
        int old_selected_idx = 0;
    };

    struct FileDialog {
        std::string file_path;
        std::string crnt_dir;
        bool show_window = true;

        void show(ListBoxState *state,
                  const std::string &base_path, const char *desc);
    };
}

#endif
