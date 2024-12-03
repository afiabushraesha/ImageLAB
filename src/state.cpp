#include "include/state.hpp"
#include "include/file_dialog.hpp"
#include "include/image.hpp"
#include "include/main_menu.hpp"
#include "include/style.hpp"

#include "g_engine/include/shader.hpp"

#include "../vendor/include/imgui/imgui.h"
#include "../vendor/include/imgui/imgui_impl_glfw.h"
#include "../vendor/include/imgui/imgui_impl_opengl3.h"

void app::State::init(g_engine::vec2<int> initial_size, const char *title,
                      g_engine::vec4<float> color) {
    window.init(initial_size, title);
    window_color = color;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.m_window, true);
    ImGui_ImplOpenGL3_Init();

    ImGuiIO &imgui_io = ImGui::GetIO();
    imgui_io.Fonts->AddFontFromFileTTF("assets/roboto_mono_medium.ttf", 20.0f);

    styleApply();
    
    #ifdef _WIN32
        home_path = std::getenv("USERPROFILE"); 
    #else
        home_path = std::getenv("HOME");
    #endif

    g_engine::shaderInitFromFile(&img_shader,
                                 "assets/img_vertex_shader.glsl", 
                                 "assets/img_fragment_shader.glsl");
    view_mat = glm::translate(glm::mat4(1.0f), {0.0f, 0.0f, -1.0f});
}

void app::State::run() {
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    const ImGuiStyle &imgui_style = ImGui::GetStyle();
    window.beginFrame(window_color);

    if (img.m_loaded && img.m_effects.m_old_gates != img.m_effects.m_gates) {
        img.passEffectDataGpu(img_shader);
        img.renderToViewport(img_shader, &img_proj_mat, view_mat);
        img.m_effects.m_old_gates = img.m_effects.m_gates;
    }

    if (img.m_loaded) {
        img.show(imgui_style.WindowPadding);
    }

    if (img_file_dialog.m_show_window) {
        dialogRenderImageImport(&img_file_dialog, &listbox_state, home_path,
                                "Select an image. The image type must be "
                                "*.jpg, *.jpeg, *.png, *.bmp or *.tga.");
    } else if (!img_file_dialog.m_path.empty()) {
        if (app::checkIfPathImage(img_file_dialog.m_path)) {
            img.init(img_file_dialog.m_path.c_str(), 480);
        }
        if (img.m_loaded) {
            img.renderToViewport(img_shader, &img_proj_mat, view_mat);
        }

        img_file_dialog.m_path.erase();
        img_file_dialog.m_crnt_dir.erase();
        listbox_state.reset();
    }

    if (img_file_dialog.m_show_window && img.m_loaded) {
        
    }

    app::renderMainMenu(&img_file_dialog, &img, img_shader,
                        &img_proj_mat, view_mat);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    window.endFrame();
}

void app::State::deinit() {
    if (img.m_loaded) {
        img.deinit();
    }

    g_engine::shaderDeinit(img_shader);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    window.deinit();
}
