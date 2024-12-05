#include "include/image.hpp"
#include "include/effect.hpp"
#include "include/path.hpp"

#include "g_engine/include/framebuffer.hpp"
#include "g_engine/include/shader.hpp"
#include "g_engine/include/texture.hpp"
#include "g_engine/include/types.hpp"
 
#include "../vendor/include/glad/glad.h"
#include "../vendor/include/imgui/imgui.h"
#include "../vendor/include/SOIL2/SOIL2.h"

#include <climits>
#include <cstring>

static g_engine::vec4<unsigned char> getPixel(const app::ImageData &data,
                                              const g_engine::vec2<size_t> &coord) {
    const int idx =
        coord.y * data.m_size.x * data.m_channels +
        coord.x * data.m_channels;

    g_engine::vec4<unsigned char> out = {
        .x = data.m_pixels[idx + 0],
        .y = data.m_pixels[idx + 1],
        .z = data.m_pixels[idx + 2],
        .w = data.m_channels == 4 ? data.m_pixels[idx + 3] : (unsigned char)0
    };

    return out;
}

static void setPixel(app::ImageData *data,
                     const g_engine::vec2<size_t> &coord,
                     const g_engine::vec4<unsigned char> &color) {
    const int idx =
        coord.y * data->m_size.x * data->m_channels +
        coord.x * data->m_channels;

    data->m_pixels[idx + 0] = color.x;
    data->m_pixels[idx + 1] = color.y;
    data->m_pixels[idx + 2] = color.z;

    if (data->m_channels == 4) {
        data->m_pixels[idx + 3] = color.w;
    }
}


static void genLowResImage(app::ImageData *out_image,
                           const app::ImageData &in_image,
                           size_t xy_divisor) {
    out_image->m_size.x = in_image.m_size.x / xy_divisor;
    out_image->m_size.y = in_image.m_size.y / xy_divisor;
    out_image->m_channels = in_image.m_channels;
    out_image->m_pixels = (unsigned char *)malloc(out_image->m_size.x *
                                                  out_image->m_size.y *
                                                  out_image->m_channels);

    g_engine::vec4<unsigned int> sum = {0, 0, 0, 0};
    g_engine::vec4<unsigned char> crnt_pixel;

    for (size_t y = 0; y < in_image.m_size.y - xy_divisor + 1; y += xy_divisor) {
        for (size_t x = 0; x < in_image.m_size.x - xy_divisor + 1; x += xy_divisor) {
            for (size_t square_y = y; square_y < y + xy_divisor; square_y++) {
                for (size_t square_x = x; square_x < x + xy_divisor; square_x++) {
                    crnt_pixel = getPixel(in_image, {square_x, square_y});
                    sum.x += crnt_pixel.x;
                    sum.y += crnt_pixel.y;
                    sum.z += crnt_pixel.z;
                    sum.w += crnt_pixel.w;
                }
            }

            sum.x /= (xy_divisor * xy_divisor);
            sum.y /= (xy_divisor * xy_divisor);
            sum.z /= (xy_divisor * xy_divisor);
            sum.w /= (xy_divisor * xy_divisor);

            setPixel(out_image, {
                (size_t)(x / xy_divisor),
                (size_t)(y / xy_divisor)
            }, {
                (unsigned char)sum.x,
                (unsigned char)sum.y,
                (unsigned char)sum.z,
                (unsigned char)sum.w,
            });

            sum = {0, 0, 0, 0};
        }
    }
}

void copyImageRef(app::ImageData *dest, const app::ImageData &source) {
    dest->m_size = source.m_size;
    dest->m_channels = source.m_channels;
    dest->m_pixels = source.m_pixels;
}

void app::Image::init(const std::string &path, int preferred_height) {
    m_data.m_pixels = SOIL_load_image(path.c_str(), &m_data.m_size.x, &m_data.m_size.y,
                                      &m_data.m_channels, SOIL_LOAD_RGBA);
    m_data.m_channels = 4;

    float aspect = (float)m_data.m_size.x / (float)m_data.m_size.y;
    m_view_size.x = aspect * preferred_height;
    m_view_size.y = preferred_height;

    if (m_data.m_size.x >= (1 << 11) || m_data.m_size.y >= (1 << 11))
        genLowResImage(&m_low_res_data, m_data, 4);
    else
        copyImageRef(&m_low_res_data, m_data);

    pathGetLast(path, m_name);

    m_id = g_engine::textureInit(m_low_res_data.m_pixels,
                                 m_low_res_data.m_size,
                                 m_low_res_data.m_channels);

    g_engine::Vertex texture_vertices[] = {
        {{                  0.0f,                  0.0f}, {0.0f, 1.0f}},
        {{                  0.0f,(float)m_data.m_size.y}, {0.0f, 0.0f}},
        {{(float)m_data.m_size.x,(float)m_data.m_size.y}, {1.0f, 0.0f}},
        {{(float)m_data.m_size.x,                  0.0f}, {1.0f, 1.0f}},
    };

    unsigned int texture_indices[] = {
        0, 1, 2,
        0, 3, 2,
    };

    m_vertex_buffer.init(sizeof(texture_vertices), texture_vertices,
                         sizeof(texture_indices), texture_indices,
                         GL_STATIC_DRAW, GL_STATIC_DRAW);
    m_framebuffer.init(m_data.m_size);
    m_effects.init();
    m_loaded = true;
}

void app::Image::deinit() {
    SOIL_free_image_data(m_data.m_pixels);
    g_engine::textureDeinit(&m_id);
    m_vertex_buffer.deinit();
    m_framebuffer.deinit();
    m_loaded = false;
}

void app::Image::passEffectDataGpu(GLuint shader) {
    glUniform1ui(glGetUniformLocation(shader, "effect_gates"),
                 m_effects.m_gates);
    glUniform1f(glGetUniformLocation(shader, "brightness_multiple"),
                m_effects.m_prop.m_brightness_multiple);
    glUniform3f(glGetUniformLocation(shader, "tint_color"),
                m_effects.m_prop.m_tint_color[0],
                m_effects.m_prop.m_tint_color[1],
                m_effects.m_prop.m_tint_color[2]);
    glUniform1f(glGetUniformLocation(shader, "noise_intensity"),
                m_effects.m_prop.m_noise_intensity);
    glUniform1f(glGetUniformLocation(shader, "contrast_intensity"),
                m_effects.m_prop.m_contrast_intensity);
    glUniform1i(glGetUniformLocation(shader, "threshold_limit"),
                m_effects.m_prop.m_threshold_limit);
}

void app::Image::renderToViewport(GLuint shader, glm::mat4 *proj_mat, const glm::mat4 &view_mat) {
    m_framebuffer.enable();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_data.m_size.x, m_data.m_size.y);

    *proj_mat = glm::ortho(0.0f, (float)m_data.m_size.x, (float)m_data.m_size.y, 0.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader, "proj"), 1, GL_FALSE, glm::value_ptr(*proj_mat));
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view_mat));

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

    ImGui::Begin("##image_preview", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Image((intptr_t)m_framebuffer.tex_id, (ImVec2){
        (float)m_view_size.x,
        (float)m_view_size.y
    });
    ImGui::End();
}

void app::Image::applyEffects() {
    g_engine::vec4<unsigned char> crnt_px;

    for (size_t y = 0; y < m_data.m_size.y; y++) {
        for (size_t x = 0; x < m_data.m_size.x; x++) {
            crnt_px = getPixel(m_data, {x, y});

            if ((m_effects.m_gates & 3) == app::EffectGrayscaleAverage) {
                app::effectGrayscaleAverageFn(&crnt_px);
            } else if ((m_effects.m_gates & 3) == app::EffectGrayscaleLumin) {
                app::effectGrayscaleLuminFn(&crnt_px);
            } else if ((m_effects.m_gates & 3) == app::EffectGrayscaleLight) {
                app::effectGrayscaleLightFn(&crnt_px);
            }

            if (m_effects.m_gates & app::EffectBrightness) {
                app::effectBrightnessFn(&crnt_px, m_effects.m_prop.m_brightness_multiple);
            }
            if (m_effects.m_gates & app::EffectTint) {
                app::effectTintFn(&crnt_px, {
                    m_effects.m_prop.m_tint_color[0],
                    m_effects.m_prop.m_tint_color[1],
                    m_effects.m_prop.m_tint_color[2],
                });
            }
            if (m_effects.m_gates & app::EffectInvert) {
                app::effectInvertFn(&crnt_px);
            }
            if (m_effects.m_gates & app::EffectThreshold) {
                app::effectThresholdFn(&crnt_px, m_effects.m_prop.m_threshold_limit);
            }

            setPixel(&m_data, {x, y}, crnt_px);
        }
    }
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

unsigned int app::imageGetSaveType(const std::string &s) {
    std::string type = s.substr(s.size() - 5, 5);
    if (type == ".jpeg") return SOIL_SAVE_TYPE_JPG;

    type = s.substr(s.size() - 4, 4);

    if (type == ".jpg") {
        return SOIL_SAVE_TYPE_JPG;
    } else if (type == ".png") {
        return SOIL_SAVE_TYPE_PNG;
    } else if (type == ".bmp") {
        return SOIL_SAVE_TYPE_BMP;
    } else if (type == ".tga") {
        return SOIL_SAVE_TYPE_TGA;
    }

    return UINT_MAX;
}
