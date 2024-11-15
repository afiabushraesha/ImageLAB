#ifndef _G_ENGINE_BUFFER_H_
#define _G_ENGINE_BUFFER_H_

#include "types.hpp"

namespace g_engine {
    struct Vertex {
        vec2<float> coord;
        vec2<float> tex_coords;
        vec3<float> color;
    };

    struct Buffer {
        unsigned int m_vao;
        unsigned int m_vbo;
        unsigned int m_ebo;

        void init(unsigned int vertices_size, Vertex *vertices,
                  unsigned int indices_size, unsigned int *indices);
        void deinit();
        void use();
    };
}

#endif
