#include "g_engine/include/window.hpp"

int main() {
    g_engine::Window window;
    window.init((g_engine::vec2<int>){640, 360}, "ImageLab");

    while (window.isOpen()) {
        window.beginFrame((g_engine::vec4<float>){0.1f, 0.1f, 0.1f, 1.0f});
        window.endFrame();
    }

    window.deinit();
}
