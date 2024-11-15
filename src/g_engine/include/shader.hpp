#ifndef _SHADER_HPP_
#define _SHADER_HPP_

namespace g_engine {
    struct Shader {
        unsigned int m_shader_bin;

        void init(const char *vs_source, const char *fs_source);
        void deinit();
        void use();
    };
}

#endif
