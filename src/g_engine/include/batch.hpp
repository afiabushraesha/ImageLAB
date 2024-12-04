#ifndef _G_ENGINE_BATCH_RENDERER_H_
#define _G_ENGINE_BATCH_RENDERER_H_

#include "buffer.hpp"
#include "types.hpp"

namespace g_engine {
    template<unsigned int square_capacity>
    struct Batch {
        Vertex m_vertices[square_capacity * 4];
        unsigned int m_indices[square_capacity * 6];
        unsigned int m_total_quads = 0;
        Buffer m_buffer;

        const unsigned int m_capacity = square_capacity;

        void init();
        void deinit();
        void beginFrame();
        void endFrame();

        void drawQuadC(vec2<float> size, vec2<float> pos, vec3<float> color);
        void drawQuadT(vec2<float> size, vec2<float> pos, const vec2<float> *texture_coords);
        void drawQuadCT(vec2<float> size, vec2<float> pos, vec3<float> color,
                        const vec2<float> *texture_coords);
    };
}

#endif
