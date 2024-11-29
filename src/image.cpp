#include "include/image.hpp"
#include "g_engine/include/framebuffer.hpp"
#include "g_engine/include/shader.hpp"
#include "g_engine/include/texture.hpp"
 
#include "../vendor/include/glad/glad.h"
#include "../vendor/include/imgui/imgui.h"
#include "../vendor/include/SOIL2/SOIL2.h"

bool app::Image::init(const char *path, int prefered_height) {
    m_pixels = SOIL_load_image(path, &m_size.x, &m_size.y,
                               &m_channels, SOIL_LOAD_RGBA);

    float aspect = (float)m_size.x / (float)m_size.y;
    m_view_size.x = aspect * prefered_height;
    m_view_size.y = prefered_height;

    if (m_pixels == NULL) {
        return false;
    }

    m_name = path;
    m_id = g_engine::textureInit(m_pixels, m_size, m_channels);

    g_engine::Vertex texture_vertices[] = {
        {{           0.0f,            0.0f}, {0.0f, 1.0f}},
        {{           0.0f, (float)m_size.y}, {0.0f, 0.0f}},
        {{(float)m_size.x, (float)m_size.y}, {1.0f, 0.0f}},
        {{(float)m_size.x,            0.0f}, {1.0f, 1.0f}},
    };

    unsigned int texture_indices[] = {
        0, 1, 2,
        0, 3, 2,
    };

    m_vertex_buffer.init(sizeof(texture_vertices), texture_vertices,
                         sizeof(texture_indices), texture_indices,
                         GL_STATIC_DRAW, GL_STATIC_DRAW);
    m_framebuffer.init(m_size);

    return true;
}

void app::Image::deinit() {
    SOIL_free_image_data(m_pixels);
    g_engine::textureDeinit(&m_id);
    m_vertex_buffer.deinit();
    m_framebuffer.deinit();
}

void app::Image::renderToViewport(GLuint shader, glm::mat4 *proj_mat, const glm::mat4 &view_mat) {
    glViewport(0, 0, m_size.x, m_size.y);

    *proj_mat = glm::ortho(0.0f, (float)m_size.x, (float)m_size.y, 0.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader, "proj"), 1, GL_FALSE, glm::value_ptr(*proj_mat));
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view_mat));
    
    m_framebuffer.enable();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    g_engine::shaderUse(shader);
    g_engine::textureUse(m_id, 0, "image_texture", shader);
    m_vertex_buffer.use();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_framebuffer.disable();
}

void app::Image::show(ImVec2 window_padding) {
    ImGui::SetNextWindowSize({
        (float)m_view_size.x + window_padding.x * 2,
        (float)m_view_size.y + window_padding.y * 2
    });

    ImGui::Begin(m_name.c_str(), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Image((intptr_t)m_framebuffer.tex_id, (ImVec2){
        (float)m_view_size.x,
        (float)m_view_size.y
    });
    ImGui::End();
}

bool app::checkIfPathImage(const std::string &s) {
    std::string type = s.substr(s.size() - 5, 5);
    if (type == ".jpeg") return true;

    type = s.substr(s.size() - 4, 4);

    if (type == ".jpg" || type == ".png" ||
        type == ".bmp" || type == ".tga") {
        return true;
    }

    return false;
}
