#include "include/main_menu.hpp"
#include "include/effect.hpp"
#include "include/effect_windows.hpp"

#include "../vendor/include/imgui/imgui.h"

void app::renderMainMenu(FileDialog *file_dialog, Image *img,
                         unsigned int shader, glm::mat4 *proj_mat, const glm::mat4 &view_mat) {
    if (!ImGui::BeginMainMenuBar()) return;

    if (ImGui::BeginMenu("File")) {
        ImGui::MenuItem("Open", "CTRL+O", &file_dialog->show_window, !img->m_loaded);
        ImGui::MenuItem("Export", "CTRL+E", false, img->m_loaded);

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("| Color Filters")) {
        ImGui::MenuItem("Grayscale", NULL, &img->m_effects.m_windows_open[EffectIdxGrayscale], img->m_loaded);
        ImGui::MenuItem("Invert", NULL, &img->m_effects.m_windows_open[EffectIdxInvert], img->m_loaded);
        ImGui::MenuItem("Threshold", NULL, &img->m_effects.m_windows_open[EffectIdxThreshold], img->m_loaded);
        ImGui::Separator();
        ImGui::MenuItem("Tint", NULL, &img->m_effects.m_windows_open[EffectIdxTint], img->m_loaded);
        ImGui::MenuItem("Contrast", NULL, false, img->m_loaded);
        ImGui::MenuItem("Brighten", NULL, &img->m_effects.m_windows_open[EffectIdxBrightness], img->m_loaded);
        ImGui::Separator();
        ImGui::MenuItem("Quantize", NULL, false, img->m_loaded);

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("| Filters")) {
        ImGui::MenuItem("Edge Detect", NULL, false, img->m_loaded);
        ImGui::MenuItem("Change Detect", NULL, false, img->m_loaded);
        ImGui::Separator();
        ImGui::MenuItem("Blur", NULL, false, img->m_loaded);
        ImGui::MenuItem("Sharpen", NULL, false, img->m_loaded);
        ImGui::Separator();
        ImGui::MenuItem("Noise", NULL, false, img->m_loaded);

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("| Crypto")) {
        ImGui::MenuItem("Encode Message (Steganography)", NULL, false, img->m_loaded);
        ImGui::MenuItem("Decode Message (Steganography)", NULL, false, img->m_loaded);

        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();

    showGrayscaleWindow(img);
    showBrightnessWindow(img, shader, proj_mat, view_mat);
    showTintWindow(img, shader, proj_mat, view_mat);
    showInvertWindow(img);
    showThresholdWindow(img, shader, proj_mat, view_mat);
}
