#ifndef _APP_STATE_H_
#define _APP_STATE_H_

#include "../g_engine/include/window.hpp"
#include "file_dialog.hpp"

namespace app {
    struct State {
        g_engine::Window window;
        g_engine::vec4<float> window_color;
        
        std::string buf;
        ListBoxState listbox_state;
        FileDialog image_file_dialog;

        void init(g_engine::vec2<int> initial_size, const char *title, g_engine::vec4<float> color);
        void run();
        void deinit();
    };
}

#endif
