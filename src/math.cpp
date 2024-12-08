#include "include/math.hpp"

#include "../vendor/include/glm/glm.hpp"

#include <cmath>

unsigned char app::mathStegnoEncodeChar(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }

    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 26;
    }

    if (c >= '0' && c <= '9') {
        return c - '0' + 52;
    }

    if (c == ' ') {
        return 62;
    }

    return 63;
}

char app::mathStegnoDecodeChar(unsigned char c) {
    if (c >= 0 && c <= 25) {
        return 'A' + c;
    }

    if (c >= 26 && c <= 51) {
        return 'a' + (c - 26);
    }
    
    if (c >= 52 && c <= 61) {
        return '0' + (c - 52);
    }

    if (c == 62) {
        return ' ';
    }

    return '\0';
}

float app::mathRandom(g_engine::vec2<float> seed) {
    return glm::fract(
        sin(
            glm::dot((glm::vec2){seed.x, seed.y},
                     {12.9898, 78.233})
        ) * 43758.5453123
    );
}

unsigned int app::mathEuclidianDistance(g_engine::vec3<unsigned char> a,
                                        g_engine::vec3<unsigned char> b) {
    return
        (a.x - b.x) * (a.x - b.x) +
        (a.y - b.y) * (a.y - b.y) +
        (a.z - b.z) * (a.z - b.z);
}

g_engine::vec3<unsigned char> app::mathRgbFromHex(unsigned int hex) {
    return {
        (unsigned char)((hex >> 24) & 0xFF),
        (unsigned char)((hex >> 16) & 0xFF),
        (unsigned char)((hex >> 8) & 0xFF)
    };
}
