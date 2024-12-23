#ifndef _APP_STATE_H_
#define _APP_STATE_H_

#include "dialog.hpp"
#include "image.hpp"

#include "../g_engine/include/window.hpp"
#include "../../vendor/include/glad/glad.h"

namespace app {
    struct State {
        g_engine::Window window;
        g_engine::vec4<float> window_color;
        
        std::string home_path;
        ListBoxState listbox_state;
        FolderContentDialog img_file_dialog;

        Image img;
        glm::mat4 img_proj_mat;
        glm::mat4 view_mat;
        GLuint img_shader;

        void init(g_engine::vec2<int> initial_size, const char *title, g_engine::vec4<float> color);
        void run();
        void deinit();
    };
}

#endif
