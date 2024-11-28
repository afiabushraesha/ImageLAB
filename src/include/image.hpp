#ifndef _APP_IMAGE_H_
#define _APP_IMAGE_H_

#include "../g_engine/include/types.hpp"
#include "../g_engine/include/buffer.hpp"
#include "../g_engine/include/framebuffer.hpp"

#include "../../vendor/include/glad/glad.h"
#include "../../vendor/include/imgui/imgui.h"

#include "../../vendor/include/glm/glm.hpp"
#include "../../vendor/include/glm/gtc/matrix_transform.hpp"
#include "../../vendor/include/glm/gtc/type_ptr.hpp"

#include <string>

namespace app {
    struct Image {
        g_engine::vec2<int> m_size;
        g_engine::vec2<int> m_view_size;
        int m_channels;
        unsigned char *m_pixels;
        GLuint m_id;
        g_engine::Buffer m_vertex_buffer;

        std::string m_name;
        g_engine::FrameBuffer m_framebuffer;

        bool init(const char *path, int prefered_height);
        void deinit();

        void renderToViewport(GLuint shader, glm::mat4 *proj_mat, const glm::mat4 &view_mat);

        void show(ImVec2 window_padding);
    };

    bool checkIfPathImage(const std::string &s);
}

#endif
