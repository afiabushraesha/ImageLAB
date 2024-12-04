#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include "../../../vendor/include/glad/glad.h"

namespace g_engine {
    void shaderInit(GLuint *shader, const char *vs_source, const char *fs_source);
    void shaderInitFromFile(GLuint *shader, const char *vs_path, const char *fs_path);
    void shaderDeinit(GLuint shader);
    void shaderUse(GLuint shader);
}

#endif
