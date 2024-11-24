#include "include/image.hpp"
#include "g_engine/include/texture.hpp"
 
#include "../vendor/include/imgui/imgui.h"
#include "../vendor/include/SOIL2/SOIL2.h"

static float i = 1.0f;

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
    return true;
}

void app::Image::deinit() {
    SOIL_free_image_data(m_pixels);
    g_engine::textureDeinit(&m_id);
}

void app::Image::show(ImVec2 window_padding) {
    ImGui::SetNextWindowSize({
        (float)m_view_size.x + window_padding.x * 2,
        (float)m_view_size.y + window_padding.y * 2
    });

    ImGui::Begin(m_name.c_str(), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Image((intptr_t)m_id, (ImVec2){
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
