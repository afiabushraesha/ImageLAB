#include "include/framebuffer.hpp"
#include "include/log.hpp"

void g_engine::FrameBuffer::init(g_engine::vec2<int> window_size) {
    glGenFramebuffers(1, &buf);
    glBindFramebuffer(GL_FRAMEBUFFER, buf);

    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window_size.x, window_size.y,
                 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_id, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    g_engine_log_error(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE,
                       "cannot complete framebuffer!\n");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void g_engine::FrameBuffer::deinit() {
    glDeleteFramebuffers(1, &buf);
}
 
void g_engine::FrameBuffer::enable() {
    glBindFramebuffer(GL_FRAMEBUFFER, buf);
}

void g_engine::FrameBuffer::disable() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
