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
        bool show_window = true;

        void show(ListBoxState *state,
                  std::string &base_path, const char *desc);
    };
}

#endif
