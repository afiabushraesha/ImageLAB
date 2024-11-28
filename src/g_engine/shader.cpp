#include "include/shader.hpp"

#include "../../vendor/include/glad/glad.h"

#include <cstdio>

static void checkShaderErrors(unsigned vsfs_shader_bin, GLenum shader_type) {
    int success;
    char log_info[512];

    glGetShaderiv(vsfs_shader_bin, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vsfs_shader_bin, 512, NULL, log_info);
        fprintf(stderr, "[error][%d:%s][%s] %s\n", __LINE__, __FILE__,
                shader_type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT", log_info);
    }
}

void g_engine::shaderInit(GLuint *shader, const char *vs_source, const char *fs_source) {
    unsigned int vs_bin = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fs_bin = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs_bin, 1, &vs_source, NULL);
    glShaderSource(fs_bin, 1, &fs_source, NULL);

    glCompileShader(vs_bin);
    glCompileShader(fs_bin);

    checkShaderErrors(vs_bin, GL_VERTEX_SHADER);
    checkShaderErrors(fs_bin, GL_FRAGMENT_SHADER);

    *shader = glCreateProgram();
    glAttachShader(*shader, vs_bin);
    glAttachShader(*shader, fs_bin);

    glDeleteShader(vs_bin);
    glDeleteShader(fs_bin);
    glLinkProgram(*shader);
}

void g_engine::shaderDeinit(GLuint shader) {
    glDeleteProgram(shader);
}

void g_engine::shaderUse(GLuint shader) {
    glUseProgram(shader);
}
