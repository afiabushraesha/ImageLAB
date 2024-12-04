#include "include/texture.hpp"

#include "../../vendor/include/glad/glad.h"

GLuint g_engine::textureInit(const unsigned char *pixels,
                             g_engine::vec2<int> texture_size, int channels) {
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_size.x, texture_size.y,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture_id;
}

void g_engine::textureDeinit(GLuint *texture_id) {
    glDeleteTextures(1, texture_id);
}

void g_engine::textureUse(GLuint texture_id, int slot,
                          const char *uniform_name, GLuint shader) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glUniform1i(glGetUniformLocation(shader, uniform_name), slot);
}
