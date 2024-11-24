#include "include/state.hpp"
#include "include/file_dialog.hpp"
#include "include/image.hpp"

#include "../vendor/include/imgui/imgui.h"
#include "../vendor/include/imgui/imgui_impl_glfw.h"
#include "../vendor/include/imgui/imgui_impl_opengl3.h"

// TODO: Implement new colorscheme
static ImVec4 hexToNormalizedRgb(unsigned int hex) {
    return ImVec4(
        ((hex      ) & 0xff) / 255.0f,
        ((hex >> 8 ) & 0xff) / 255.0f,
        ((hex >> 16) & 0xff) / 255.0f,
        ((hex >> 24) & 0xff) / 255.0f
    );
}

void app::State::init(g_engine::vec2<int> initial_size, const char *title,
                      g_engine::vec4<float> color) {
    window.init(initial_size, title);
    window_color = color;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.m_window, true);
    ImGui_ImplOpenGL3_Init();

    ImGuiIO &imgui_io = ImGui::GetIO();
    imgui_io.Fonts->AddFontFromFileTTF("assets/roboto_mono_medium.ttf", 16.0f);

    ImGuiStyle &imgui_style = ImGui::GetStyle();

    // TODO: Implement new colorscheme
    //imgui_style.WindowRounding = 0;
    //imgui_style.FrameRounding = 0;
    //imgui_style.ScrollbarRounding = 0;

    //imgui_style.Colors[ImGuiCol_Text]                  = ImVec4();
    //imgui_style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    //imgui_style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
    //imgui_style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
    //imgui_style.Colors[ImGuiCol_Border]                = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
    //imgui_style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    //imgui_style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
    //imgui_style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
    //imgui_style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
    //imgui_style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
    //imgui_style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
    //imgui_style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
    //imgui_style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
    //imgui_style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    //imgui_style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
    //imgui_style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
    //imgui_style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
    //imgui_style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
    //imgui_style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
    //imgui_style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
    //imgui_style.Colors[ImGuiCol_Button]                = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
    //imgui_style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
    //imgui_style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
    //imgui_style.Colors[ImGuiCol_Header]                = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
    //imgui_style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
    //imgui_style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
    //imgui_style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    //imgui_style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    //imgui_style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    //imgui_style.Colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    //imgui_style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    //imgui_style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    //imgui_style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    //imgui_style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);


    home_path = std::getenv("HOME");
}

void app::State::run() {
    const ImGuiStyle &imgui_style = ImGui::GetStyle();
    window.beginFrame(window_color);
    
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    if (img_file_dialog.show_window) {
        img_file_dialog.show(&listbox_state, home_path,
                             "Select an image. The image type must be "
                             "*.jpg, *.jpeg, *.png, *.bmp or *.tga.");
    } else if (!img_file_dialog.file_path.empty() && app::checkIfPathImage(img_file_dialog.file_path)) {
        app::Image img;
        
        if (img.init(img_file_dialog.file_path.c_str(), 480)) {
            imgs.push_back(img);
        }

        img_file_dialog.file_path.erase();
    }

    for (app::Image &img : imgs) {
        img.show(imgui_style.WindowPadding);
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    window.endFrame();
}

void app::State::deinit() {
    for (app::Image &img : imgs) {
        img.deinit();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    window.deinit();
}
