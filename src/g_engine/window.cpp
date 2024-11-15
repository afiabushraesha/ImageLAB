#include "include/window.hpp"
#include "include/log.hpp"

#include "../../vendor/include/glad/glad.h"
#include "../../vendor/include/glfw/glfw3.h"

void g_engine::Window::init(vec2<int> size, const char *title) {
    m_size = size;
    m_title = title;

    g_engine_log_error(!glfwInit(), "failed to initialize glfw!\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    #endif

    m_window = glfwCreateWindow(m_size.x, m_size.y, title, NULL, NULL);
    
    g_engine_log_error(m_window == NULL, "failed to create window!\n");
    glfwMakeContextCurrent(m_window);

    g_engine_log_error(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress),
                       "failed to initialize opengl!\n");

    glViewport(0, 0, m_size.x, m_size.y);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void g_engine::Window::deinit() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool g_engine::Window::isOpen() {
    return !glfwWindowShouldClose(m_window);
}

void g_engine::Window::beginFrame(vec4<float> color) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color.x, color.y, color.z, color.w);
}

void g_engine::Window::endFrame() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}
