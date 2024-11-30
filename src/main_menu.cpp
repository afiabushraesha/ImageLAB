#include "include/main_menu.hpp"

#include "../vendor/include/imgui/imgui.h"

void app::renderMainMenu(FileDialog *file_dialog) {
    if (!ImGui::BeginMainMenuBar()) return;

    if (ImGui::BeginMenu("File")) {
        ImGui::MenuItem("Open", "CTRL+O", &file_dialog->show_window);
        if (file_dialog->show_window == false) {
            file_dialog->crnt_dir.erase();
        }
        ImGui::MenuItem("Export", "CTRL+E", false, false);

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("| Color Filters")) {
        ImGui::MenuItem("Grayscale", NULL, false, false);
        ImGui::MenuItem("Invert", NULL, false, false);
        ImGui::Separator();
        ImGui::MenuItem("Tint", NULL, false, false);
        ImGui::MenuItem("Contrast", NULL, false, false);
        ImGui::MenuItem("Brighten", NULL, false, false);
        ImGui::Separator();
        ImGui::MenuItem("Quantize", NULL, false, false);

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("| Filters")) {
        ImGui::MenuItem("Edge Detect", NULL, false, false);
        ImGui::MenuItem("Change Detect", NULL, false, false);
        ImGui::Separator();
        ImGui::MenuItem("Blur", NULL, false, false);
        ImGui::MenuItem("Sharpen", NULL, false, false);
        ImGui::Separator();
        ImGui::MenuItem("Noise", NULL, false, false);

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("| Crypto")) {
        ImGui::MenuItem("Encode Message (Steganography)", NULL, false, false);
        ImGui::MenuItem("Decode Message (Steganography)", NULL, false, false);

        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
}
