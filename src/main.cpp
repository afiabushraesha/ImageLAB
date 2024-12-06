#include "include/state.hpp"

int main() {
    app::State state;
    state.init({1280, 720}, "ImageLAB", {
        17  / 255.0f,
        17  / 255.0f,
        27  / 255.0f,
        255 / 255.0f
    });

    while (state.window.isOpen()) {
        state.run();
    }

    state.deinit();
}
