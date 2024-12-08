#ifndef _APP_MATH_H_
#define _APP_MATH_H_

#include "../g_engine/include/types.hpp"

namespace app {
    unsigned char mathStegnoEncodeChar(char c);
    char mathStegnoDecodeChar(unsigned char c);
    float mathRandom(g_engine::vec2<float> seed);
    unsigned int mathEuclidianDistance(g_engine::vec3<unsigned char> a,
                                       g_engine::vec3<unsigned char> b);
    g_engine::vec3<unsigned char> mathRgbFromHex(unsigned int hex);
}

#endif
