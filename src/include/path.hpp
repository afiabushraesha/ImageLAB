#ifndef _APP_PATH_H_
#define _APP_PATH_H_

#include <string>

namespace app {
    void pathAppend(std::string *s, const std::string &appendix);
    void pathRemoveLast(std::string &s);
    void pathGetLast(const std::string &s, char *out_last);
}

#endif
