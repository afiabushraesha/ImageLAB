#ifndef _APP_IMAGE_H_
#define _APP_IMAGE_H_

#include "effect.hpp"

#include "../g_engine/include/types.hpp"
#include "../g_engine/include/buffer.hpp"
#include "../g_engine/include/framebuffer.hpp"

#include "../../vendor/include/glad/glad.h"
#include "../../vendor/include/imgui/imgui.h"

#include "../../vendor/include/glm/glm.hpp"
#include "../../vendor/include/glm/gtc/matrix_transform.hpp"
#include "../../vendor/include/glm/gtc/type_ptr.hpp"

#include <string>
#include <pthread.h>

namespace app {
    struct ImageData {
        unsigned char *m_pixels;
        int m_channels;
        g_engine::vec2<int> m_size;
    };

    struct ImageThreadData {
        // [0] is on -> thread has began.
        // [1] is on -> thread's job is done.
        unsigned char m_state = 0;
        ImageData *m_data;
        Effects *m_effects_data;
    };

    struct Image {
        ImageData m_data;
        ImageData m_low_res_data;
        g_engine::vec2<int> m_view_size;
        float m_aspect_ratio;

        g_engine::vec3<unsigned char> m_max_intensity = {0, 0, 0};
        g_engine::vec3<unsigned char> m_min_intensity = {255, 255, 255};

        GLuint m_id;
        g_engine::Buffer m_vertex_buffer;
        g_engine::FrameBuffer m_framebuffer;

        Effects m_effects;

        char m_name[256];
        size_t m_name_size = sizeof(m_name);
        bool m_loaded = false;

        void init(const std::string &path, int preferred_height);
        void deinit();

        void passEffectDataGpu(GLuint shader);
        void renderToViewport(GLuint shader, glm::mat4 *proj_mat, const glm::mat4 &view_mat);
        void applyEffects();

        void show(ImVec2 window_padding);
    };

    bool checkIfPathImage(const std::string &s);
    unsigned int imageGetSaveType(const std::string &s);
}

#endif
