#ifndef _APP_DIR_WINDOW_H_
#define _APP_DIR_WINDOW_H_

#include <cstddef>
#include <string>

namespace app {
    struct ListBoxState {
        bool selected = false;
        int selected_idx = -1;
        int old_selected_idx = 0;
    };

    struct DirListResult {
        char buf[256];
        const size_t buf_size = 256;
        bool show_window = true;
    };

    void showDirList(DirListResult *result, ListBoxState *state,
                     std::string &base_path, const char *desc);
}

#endif
