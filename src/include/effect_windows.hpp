#ifndef _APP_EFFECT_WINDOW_H_
#define _APP_EFFECT_WINDOW_H_

#include "image.hpp"

namespace app {
    void showGrayscaleWindow(Image *img);
    void showBrightnessWindow(Image *img, unsigned int shader,
                              glm::mat4 *proj_mat, const glm::mat4 &view_mat);
    void showTintWindow(Image *img, unsigned int shader,
                        glm::mat4 *proj_mat, const glm::mat4 &view_mat);
    void showInvertWindow(Image *img);
    void showThresholdWindow(Image *img, unsigned int shader,
                             glm::mat4 *proj_mat, const glm::mat4 &view_mat);
}

#endif