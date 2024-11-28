#ifndef _G_ENGINE_FRAMEBUFFER_H_
#define _G_ENGINE_FRAMEBUFFER_H_

#include "types.hpp"
#include "../../../vendor/include/glad/glad.h"

namespace g_engine {
    struct FrameBuffer {
        GLuint buf;    
        GLuint tex_id;

        void init(g_engine::vec2<int> window_size);
        void deinit();
        void enable();
        void disable();
    };
}

#endif
