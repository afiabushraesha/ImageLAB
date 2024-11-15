#ifndef _G_ENGINE_WINDOW_HPP_
#define _G_ENGINE_WINDOW_HPP_

#include "types.hpp"

struct GLFWwindow;

namespace g_engine {
    struct Window {
        GLFWwindow *m_window;
        vec2<int> m_size;
        const char *m_title;

        void init(vec2<int> size, const char *title);
        void deinit();
        bool isOpen();
        void beginFrame(vec4<float> color);
        void endFrame();
    };
}

#endif
