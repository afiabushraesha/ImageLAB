#ifndef _APP_IMAGE_H_
#define _APP_IMAGE_H_

#include "../../vendor/include/glad/glad.h"
#include "../../vendor/include/imgui/imgui.h"

#include "../g_engine/include/types.hpp"

#include <string>

namespace app {
    struct Image {
        g_engine::vec2<int> m_size;
        g_engine::vec2<int> m_view_size;
        int m_channels;
        unsigned char *m_pixels;
        GLuint m_id;
        std::string m_name;

        bool init(const char *path, int prefered_height);
        void deinit();
        void show(ImVec2 window_padding);
    };

    bool checkIfPathImage(const std::string &s);
}

#endif
