#ifndef _G_ENGINE_LOG_H_
#define _G_ENGINE_LOG_H_

#include <string>

void _g_engine_log_log(int line, const char *file, bool cond, const std::string &msg);
void _g_engine_log_warn(int line, const char *file, bool cond, const std::string &msg);
void _g_engine_log_error(int line, const char *file, bool cond, const std::string &msg);

#define g_engine_log_log(condition, msg) _g_engine_log_log(__LINE__, __FILE__, condition, msg);
#define g_engine_log_warn(condition, msg) _g_engine_log_warn(__LINE__, __FILE__, condition, msg);
#define g_engine_log_error(condition, msg) _g_engine_log_error(__LINE__, __FILE__, condition, msg);

#endif
