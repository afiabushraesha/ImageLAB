#include "include/buffer.hpp"

#include "../../vendor/include/glad/glad.h"
#include <cstddef>

void g_engine::Buffer::init(unsigned int vertices_size, Vertex *vertices,
                            unsigned int indices_size, unsigned int *indices,
                            GLenum vertices_draw_method, GLenum indices_draw_method) {
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, vertices_draw_method);

    if (indices_size != 0 && indices != NULL) {
        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, indices_draw_method);
    }

    // vertex coordinates
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    if (indices_size != 0 && indices != NULL) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

void g_engine::Buffer::deinit() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
}

void g_engine::Buffer::use() {
    glBindVertexArray(m_vao);
}
