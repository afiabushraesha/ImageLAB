#include "include/batch.hpp"

#include "../../vendor/include/glad/glad.h"
#include <cstddef>

template<unsigned int cap>
void g_engine::Batch<cap>::init() {
    int a = 0;
    for (int i = 0; i < cap * 6; i += 6) {
        m_indices[i + 0] = a + 0;
        m_indices[i + 1] = a + 1;
        m_indices[i + 2] = a + 2;
        m_indices[i + 3] = a + 0;
        m_indices[i + 4] = a + 3;
        m_indices[i + 5] = a + 2;
        a += 4;
    }

    m_buffer.init(sizeof(m_vertices), NULL, sizeof(m_indices), m_indices);
}

template<unsigned int cap>
void g_engine::Batch<cap>::deinit() {
    m_buffer.deinit();
}

template<unsigned int cap>
void g_engine::Batch<cap>::beginFrame() {
    m_total_quads = 0;
}

template<unsigned int cap>
void g_engine::Batch<cap>::endFrame() {
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer.m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_total_quads * sizeof(Vertex) * 4, m_vertices);
    glBindVertexArray(m_buffer.m_vao);
    glDrawElements(GL_TRIANGLES, m_total_quads * 6, GL_UNSIGNED_INT, 0);
}

template<unsigned int cap>
void g_engine::Batch<cap>::drawQuadC(vec2<float> size, vec2<float> pos,
                                     vec3<float> color) {
    if (m_total_quads == cap) {
        endFrame();
        beginFrame();
    }

    float x = size.x / 2;
    float y = size.y / 2;

    m_vertices[m_total_quads * 4 + 0] = {{-x + pos.x, y + pos.y}, {0.0f, 1.0f}, color};
    m_vertices[m_total_quads * 4 + 1] = {{-x + pos.x,-y + pos.y}, {0.0f, 0.0f}, color};
    m_vertices[m_total_quads * 4 + 2] = {{ x + pos.x,-y + pos.y}, {1.0f, 0.0f}, color};
    m_vertices[m_total_quads * 4 + 3] = {{ x + pos.x, y + pos.y}, {1.0f, 1.0f}, color};

    m_total_quads++;
}

template<unsigned int cap>
void g_engine::Batch<cap>::drawQuadT(vec2<float> size, vec2<float> pos,
                                     const vec2<float> *texture_coords) {
    if (m_total_quads == cap) {
        endFrame();
        beginFrame();
    }

    float x = size.x / 2;
    float y = size.y / 2;

    m_vertices[m_total_quads * 4 + 0] = {{-x + pos.x, y + pos.y}, {texture_coords[0]}, {1.0f, 1.0f, 1.0f}};
    m_vertices[m_total_quads * 4 + 1] = {{-x + pos.x,-y + pos.y}, {texture_coords[1]}, {1.0f, 1.0f, 1.0f}};
    m_vertices[m_total_quads * 4 + 2] = {{ x + pos.x,-y + pos.y}, {texture_coords[2]}, {1.0f, 1.0f, 1.0f}};
    m_vertices[m_total_quads * 4 + 3] = {{ x + pos.x, y + pos.y}, {texture_coords[3]}, {1.0f, 1.0f, 1.0f}};

    m_total_quads++;
}

template<unsigned int cap>
void g_engine::Batch<cap>::drawQuadCT(vec2<float> size, vec2<float> pos,
                                      vec3<float> color, const vec2<float> *texture_coords) {
    if (m_total_quads == cap) {
        endFrame();
        beginFrame();
    }

    float x = size.x / 2;
    float y = size.y / 2;

    m_vertices[m_total_quads * 4 + 0] = {{-x + pos.x, y + pos.y}, {texture_coords[0]}, color};
    m_vertices[m_total_quads * 4 + 1] = {{-x + pos.x,-y + pos.y}, {texture_coords[1]}, color};
    m_vertices[m_total_quads * 4 + 2] = {{ x + pos.x,-y + pos.y}, {texture_coords[2]}, color};
    m_vertices[m_total_quads * 4 + 3] = {{ x + pos.x, y + pos.y}, {texture_coords[3]}, color};

    m_total_quads++;
}
