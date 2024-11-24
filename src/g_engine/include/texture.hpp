#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../../../vendor/include/glad/glad.h"
#include "types.hpp"

struct img_pixmap;

namespace g_engine {
    struct Shader;

    GLuint textureInit(const unsigned char *pixels, g_engine::vec2<int> texture_size, int channels);
    void textureDeinit(unsigned int *texture_id);
    void textureUse(unsigned int *texture_id, int slot, const char *uniform_name, g_engine::Shader *shader);
}

#endif
