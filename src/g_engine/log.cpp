#include "include/log.hpp"
#include <cstdio>

void _g_engine_log_log(int line, const char *file, bool cond, const std::string &msg) {
    if (cond) fprintf(stderr, "[log][%s:%d] %s", file, line, msg.c_str());
}

void _g_engine_log_warn(int line, const char *file, bool cond, const std::string &msg) {
    if (cond) fprintf(stderr, "[warn][%s:%d] %s", file, line, msg.c_str());
}

void _g_engine_log_error(int line, const char *file, bool cond, const std::string &msg) {
    if (cond) fprintf(stderr, "[error][%s:%d] %s", file, line, msg.c_str());
}
