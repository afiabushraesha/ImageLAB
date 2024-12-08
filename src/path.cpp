#include "include/path.hpp"

void app::pathAppend(std::string *s, const std::string &appendix) {
    char c =
        #ifdef _WIN32
            '\\';
        #else
            '/';
        #endif

    if (s->back() != c) s->push_back(c);
    s->append(appendix);
}

void app::pathRemoveLast(std::string &s) {
    char c =
        #ifdef _WIN32
            '\\';
        #else
            '/';
        #endif

    size_t i = s.size() - 1;
    while (s[i] != c) i--;

    if (i == 0) return;
    s.resize(s.size() - (s.size() - i));
}

void app::pathGetLast(const std::string &s, char *out_last) {
    size_t j = 0;
    for (size_t i = s.size() - 1; i >= 0; i--) {
        if (s[i] == '/' || s[i] == '\\') {
            break;
        }
        out_last[j++] = s[i];
    }

    for (int i = 0; i < j / 2; i++) {
        std::swap(out_last[i], out_last[j - i - 1]);
    }
}
