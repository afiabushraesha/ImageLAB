#include "include/effect_windows.hpp"
#include "include/effect.hpp"

#include "../vendor/include/imgui/imgui.h"

void app::showGrayscaleWindow(Image *img) {
    bool *is_open = &img->m_effects.m_windows_open[EffectIdxGrayscale];

    if (!*is_open) {
        return;
    }

    if ((!ImGui::Begin("Grayscale", is_open))) {
        ImGui::End();
        return;
    }

    ImGui::RadioButton("Average", &img->m_effects.m_prop.m_ui_info.m_grayscale_idx, EffectGrayscaleAverage);
    ImGui::RadioButton("Lumin", &img->m_effects.m_prop.m_ui_info.m_grayscale_idx, EffectGrayscaleLumin);
    ImGui::RadioButton("Lightness", &img->m_effects.m_prop.m_ui_info.m_grayscale_idx, EffectGrayscaleLight);

    img->m_effects.m_gates &= ~(unsigned int)3;
    img->m_effects.m_gates |= img->m_effects.m_prop.m_ui_info.m_grayscale_idx;

    ImGui::TextWrapped("Converts a colorful image\ninto a black-white image.\n"
                       "\t- Average is simply the\n\t  average between RGB channels.\n"
                       "\t- Lumin multiples eye corrected\n\t  values with RGB channels.\n"
                       "\t- Lightness is the average\n\t  between Max and Min of RGB Channels.\n");

    if (ImGui::Button("Ok")) {
        *is_open = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel")) {
        img->m_effects.m_gates &= ~(unsigned int)3;
        *is_open = false;
    }

    ImGui::End();
}

void app::showBrightnessWindow(Image *img, unsigned int shader,
                               glm::mat4 *proj_mat, const glm::mat4 &view_mat) {
    bool *is_open = &img->m_effects.m_windows_open[EffectIdxBrightness];

    if (!*is_open) {
        return;
    }

    if ((!ImGui::Begin("Brightness", is_open))) {
        ImGui::End();
        return;
    }

    if (ImGui::SliderFloat("multiple",
                           &img->m_effects.m_prop.m_brightness_multiple, 0.0f, 3.0f)) {
        img->passEffectDataGpu(shader);
        img->renderToViewport(shader, proj_mat, view_mat);
    }
    ImGui::TextWrapped("Multiples each pixel value with the given multiple. "
                       "Resulting in a brighter image.");

    img->m_effects.m_gates |= EffectBrightness;

    if (ImGui::Button("Ok")) {
        *is_open = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel")) {
        img->m_effects.m_gates &= ~EffectBrightness;
        *is_open = false;
    }

    ImGui::End();
}

void app::showTintWindow(Image *img, unsigned int shader,
                         glm::mat4 *proj_mat, const glm::mat4 &view_mat) {
    bool *is_open = &img->m_effects.m_windows_open[EffectIdxTint];

    if (!*is_open) {
        return;
    }

    if ((!ImGui::Begin("Tint", is_open))) {
        ImGui::End();
        return;
    }

    if (ImGui::SliderFloat("R", &img->m_effects.m_prop.m_tint_color[0], 0.0f, 3.0f)) {
        img->passEffectDataGpu(shader);
        img->renderToViewport(shader, proj_mat, view_mat);
    }
    if (ImGui::SliderFloat("G", &img->m_effects.m_prop.m_tint_color[1], 0.0f, 3.0f)) {
        img->passEffectDataGpu(shader);
        img->renderToViewport(shader, proj_mat, view_mat);
    }
    if (ImGui::SliderFloat("B", &img->m_effects.m_prop.m_tint_color[2], 0.0f, 3.0f)) {
        img->passEffectDataGpu(shader);
        img->renderToViewport(shader, proj_mat, view_mat);
    }

    ImGui::TextWrapped("Multiples pixel's RGB values with given RGB values.");

    img->m_effects.m_gates |= EffectTint;

    if (ImGui::Button("Ok")) {
        *is_open = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel")) {
        img->m_effects.m_gates &= ~EffectTint;
        *is_open = false;
    }

    ImGui::End();
}

void app::showThresholdWindow(Image *img, unsigned int shader,
                              glm::mat4 *proj_mat, const glm::mat4 &view_mat) {
    bool *is_open = &img->m_effects.m_windows_open[EffectIdxThreshold];

    if (!*is_open) {
        return;
    }

    if ((!ImGui::Begin("Threshold", is_open))) {
        ImGui::End();
        return;
    }

    if (ImGui::SliderInt("Limit", &img->m_effects.m_prop.m_threshold_limit, 0, 255)) {
        img->passEffectDataGpu(shader);
        img->renderToViewport(shader, proj_mat, view_mat);
    }
    ImGui::TextWrapped("Clamps pixel's value to the maximum of RGB(255) if "
                       "it's above Limit, otherwise it's set to 0.");

    img->m_effects.m_gates |= EffectThreshold;

    if (ImGui::Button("Ok")) {
        *is_open = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel")) {
        img->m_effects.m_gates &= ~EffectThreshold;
        *is_open = false;
    }

    ImGui::End();
}
