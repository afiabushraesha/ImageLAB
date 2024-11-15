#include "include/texture.hpp"
#include "include/shader.hpp"

#include "../../vendor/include/imago2/imago2.h"
#include "../../vendor/include/glad/glad.h"

void g_engine::Texture::init(img_pixmap img) {
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, img.pixelsz == 3 ? GL_RGB : GL_RGBA, img.width,
                 img.height, 0, img.pixelsz == 3 ? GL_RGB : GL_RGBA,
                 GL_UNSIGNED_BYTE, img.pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void g_engine::Texture::deinit() {
    glDeleteTextures(1, &m_texture);
}

void g_engine::Texture::use(int slot, const char *uniform_name, g_engine::Shader *shader) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glUniform1i(glGetUniformLocation(shader->m_shader_bin, uniform_name), slot);
}
