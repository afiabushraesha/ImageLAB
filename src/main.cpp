#include "include/state.hpp"
#include <iostream>

int main() {
    app::State state;
    state.init({640, 360}, "ImageLAB", {0.1f, 0.1f, 0.1f, 1.0f});

    while (state.window.isOpen()) {
        state.run();
    }

    state.deinit();
}
