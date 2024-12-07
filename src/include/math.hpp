#ifndef _APP_MATH_H_
#define _APP_MATH_H_

#include "../g_engine/include/types.hpp"

namespace app {
    unsigned char mathStegnoEncodeChar(char c);
    char mathStegnoDecodeChar(unsigned char c);
    float mathRandom(g_engine::vec2<float> seed);
}

#endif
