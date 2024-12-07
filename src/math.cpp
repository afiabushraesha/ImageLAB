#include "include/math.hpp"

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
