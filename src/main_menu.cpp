#include "include/main_menu.hpp"
#include "include/effect.hpp"
#include "include/effect_windows.hpp"
#include "include/dialog.hpp"

#include "../vendor/include/imgui/imgui.h"

void app::renderMainMenu(FolderContentDialog *file_dialog, Image *img,
                         unsigned int shader, glm::mat4 *proj_mat, const glm::mat4 &view_mat) {
    if (!ImGui::BeginMainMenuBar()) {
        ImGui::EndMenuBar();
        return;
    }

    if (ImGui::BeginMenu("File")) {
        ImGui::MenuItem("Open", "CTRL+O", &file_dialog->m_show_window, !img->m_loaded);
        ImGui::MenuItem("Export", "CTRL+E", &file_dialog->m_show_window, img->m_loaded);

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("| Filters")) {
        ImGui::MenuItem("Grayscale", NULL, &img->m_effects.m_windows_open[EffectIdxGrayscale], img->m_loaded);
        ImGui::MenuItem("Invert", NULL, &img->m_effects.m_windows_open[EffectIdxInvert], img->m_loaded);
        ImGui::MenuItem("Threshold", NULL, &img->m_effects.m_windows_open[EffectIdxThreshold], img->m_loaded);
        ImGui::MenuItem("Noise", NULL, &img->m_effects.m_windows_open[EffectIdxNoise], img->m_loaded);
        ImGui::Separator();
        ImGui::MenuItem("Tint", NULL, &img->m_effects.m_windows_open[EffectIdxTint], img->m_loaded);
        ImGui::MenuItem("Contrast", NULL, &img->m_effects.m_windows_open[EffectIdxContrast], img->m_loaded);
        ImGui::MenuItem("Brighten", NULL, &img->m_effects.m_windows_open[EffectIdxBrightness], img->m_loaded);
        ImGui::Separator();
        ImGui::MenuItem("Quantize", NULL, &img->m_effects.m_windows_open[EffectIdxBrightness], img->m_loaded);

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("| Crypto")) {
        ImGui::MenuItem("Encode Message (Steganography)", NULL,
                        &img->m_effects.m_windows_open[EffectIdxStegnographyEncode], img->m_loaded);
        ImGui::MenuItem("Decode Message (Steganography)", NULL,
                        &img->m_effects.m_windows_open[EffectIdxStegnographyDecode], img->m_loaded);

        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();

    if (img->m_loaded) {
        showGrayscaleWindow(img);
        showBrightnessWindow(img, shader, proj_mat, view_mat);
        showTintWindow(img, shader, proj_mat, view_mat);
        if (img->m_effects.m_windows_open[EffectIdxInvert]) {
            img->m_effects.m_gates |= EffectInvert;
        } else {
            img->m_effects.m_gates &= ~EffectInvert;
        }
        showThresholdWindow(img, shader, proj_mat, view_mat);
        if (img->m_effects.m_windows_open[EffectIdxContrast]) {
            img->m_effects.m_gates |= EffectContrast;
        } else {
            img->m_effects.m_gates &= ~EffectContrast;
        }
        showNoiseWindow(img, shader, proj_mat, view_mat);
        showStegnographyEncodeWindow(img);
        showStegnographyDecodeWindow(img);
        showQuantizeWindow(img, shader, proj_mat, view_mat);
    }
}
