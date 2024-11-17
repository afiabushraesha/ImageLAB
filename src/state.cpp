#include "include/state.hpp"
#include "include/dir_window.hpp"

#include "../vendor/include/imgui/imgui.h"
#include "../vendor/include/imgui/imgui_impl_glfw.h"
#include "../vendor/include/imgui/imgui_impl_opengl3.h"

#include <cstdlib>

void app::State::init(g_engine::vec2<int> initial_size, const char *title,
                 g_engine::vec4<float> color) {
    window.init(initial_size, title);
    window_color = color;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.m_window, true);
    ImGui_ImplOpenGL3_Init();

    ImGuiIO &imgui_io = ImGui::GetIO();
    imgui_io.Fonts->AddFontFromFileTTF("assets/roboto_mono_medium.ttf", 18.0f);

    buf = std::getenv("HOME");
}

void app::State::run() {
    window.beginFrame(window_color);
    
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    app::showDirList(&dir_result, &listbox_state, buf,"here is a short description!");
    ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    window.endFrame();
}

void app::State::deinit() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    window.deinit();
}
