#ifndef _G_ENGINE_BUFFER_H_
#define _G_ENGINE_BUFFER_H_

#include "types.hpp"

#include "../../../vendor/include/glad/glad.h"

namespace g_engine {
    struct Vertex {
        float coord[2];
        float tex_coords[2];
    };

    struct Buffer {
        unsigned int m_vao;
        unsigned int m_vbo;
        unsigned int m_ebo;

        void init(unsigned int vertices_size, Vertex *vertices,
                  unsigned int indices_size, unsigned int *indices,
                  GLenum vertices_draw_method, GLenum indices_draw_method);
        void deinit();
        void use();
    };
}

#endif
