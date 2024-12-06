#include "include/effect.hpp"

#include <cstring>
#include <algorithm>

void app::Effects::init() {
    memset(m_windows_open, false, sizeof(m_windows_open));
}

void app::Effects::reset() {
    m_prop.m_ui_info.m_grayscale_idx = EffectGrayscaleAverage;
    m_prop.m_brightness_multiple = 1.0f;

    m_prop.m_tint_color[0] = 1.0f;
    m_prop.m_tint_color[1] = 1.0f;
    m_prop.m_tint_color[2] = 1.0f;

    m_prop.m_noise_intensity = 0.5f;
    m_prop.m_contrast_intensity = 1.0f;
    m_prop.m_is_inverted = false;
    m_prop.m_threshold_limit = 127;
}

void app::effectGrayscaleAverageFn(g_engine::vec4<unsigned char> *px) {
    unsigned char y = (px->x + px->y + px->z) / 3.0f;
    px->x = px->y = px->z = y;
}

void app::effectGrayscaleLuminFn(g_engine::vec4<unsigned char> *px) {
    unsigned char y = (0.299f * px->x) + (0.587f * px->y) + (0.114f * px->z);
    px->x = px->y = px->z = y;
}

void app::effectGrayscaleLightFn(g_engine::vec4<unsigned char> *px) {
    unsigned char y = (std::min(px->x, std::min(px->y, px->z)) + 
                       std::max(px->x, std::max(px->y, px->z))) / 2.0f;
    px->x = px->y = px->z = y;
}

void app::effectBrightnessFn(g_engine::vec4<unsigned char> *px, float multiple) {
    px->x = (unsigned char)std::clamp((int)(px->x * multiple), 0, 255);
    px->y = (unsigned char)std::clamp((int)(px->y * multiple), 0, 255);
    px->z = (unsigned char)std::clamp((int)(px->z * multiple), 0, 255);
}

void app::effectTintFn(g_engine::vec4<unsigned char> *px, g_engine::vec3<float> color) {
    px->x = (unsigned char)std::clamp((int)(px->x * color.x), 0, 255);
    px->y = (unsigned char)std::clamp((int)(px->y * color.y), 0, 255);
    px->z = (unsigned char)std::clamp((int)(px->z * color.z), 0, 255);
}

void app::effectContrastFn(g_engine::vec4<unsigned char> *px,
                           g_engine::vec3<unsigned char> min_intensity,
                           g_engine::vec3<unsigned char> max_intensity) {
    px->x = ((float)(px->x - min_intensity.x) / (float)(max_intensity.x - min_intensity.x)) * 255;
    px->y = ((float)(px->y - min_intensity.y) / (float)(max_intensity.y - min_intensity.y)) * 255;
    px->z = ((float)(px->z - min_intensity.z) / (float)(max_intensity.z - min_intensity.z)) * 255;
}
//
//void app::effectQuantizeFn(g_engine::vec4<unsigned char> px) {
//
//}
//
//void app::effectNoiseFn(g_engine::vec4<unsigned char> px) {
//
//}
//
//void app::effectChangeDetectFn(g_engine::vec4<unsigned char> px) {
//
//}
//
void app::effectInvertFn(g_engine::vec4<unsigned char> *px) {
    px->x = (unsigned char)(255 - px->x);
    px->y = (unsigned char)(255 - px->y);
    px->z = (unsigned char)(255 - px->z);
}

void app::effectThresholdFn(g_engine::vec4<unsigned char> *px, unsigned int threshold) {
    effectGrayscaleLuminFn(px);
    if (px->x >= threshold) px->x = px->y = px->z = 255;
    else px->x = px->y = px->z = 0;
}
