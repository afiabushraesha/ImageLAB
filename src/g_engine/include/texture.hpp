#ifndef _TEXTURE_H_
#define _TEXTURE_H_

struct img_pixmap;

namespace g_engine {
    struct Shader;

    struct Texture {
        unsigned int m_texture;

        void init(img_pixmap img);
        void deinit();
        void use(int slot, const char *uniform_name, g_engine::Shader *shader);
    };
}

#endif
