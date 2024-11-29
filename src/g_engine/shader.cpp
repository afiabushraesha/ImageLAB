#include "include/shader.hpp"
#include "include/log.hpp"

#include "../../vendor/include/glad/glad.h"

#include <cstdio>
#include <fstream>
#include <string>

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

void g_engine::shaderInitFromFile(GLuint *shader, const char *vs_path,
                                  const char *fs_path) {
    std::ifstream file(vs_path);
    std::string vs_source, fs_source, line;

    g_engine_log_error(!file.is_open(),
                       "failed to open vertex shader file!");

    while (std::getline(file, line, '\n')) {
        vs_source.append(line + '\n');
    }

    file.close();

    file.open(fs_path); 
    g_engine_log_error(!file.is_open(),
                       "failed to open fragment shader file!");

    while (std::getline(file, line, '\n')) {
        fs_source.append(line + '\n');
    }

    file.close();

    g_engine::shaderInit(shader, vs_source.c_str(), fs_source.c_str());
}

void g_engine::shaderDeinit(GLuint shader) {
    glDeleteProgram(shader);
}

void g_engine::shaderUse(GLuint shader) {
    glUseProgram(shader);
}
