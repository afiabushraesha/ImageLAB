#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "types.hpp"

#include "../../../vendor/include/glad/glad.h"

struct img_pixmap;

namespace g_engine {
    GLuint textureInit(const unsigned char *pixels, g_engine::vec2<int> texture_size, int channels);
    void textureDeinit(unsigned int *texture_id);
    void textureUse(GLuint texture_id, int slot, const char *uniform_name, GLuint shader);
}

#endif
