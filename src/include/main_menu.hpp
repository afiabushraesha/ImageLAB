#ifndef _APP_MAIN_MENU_H_
#define _APP_MAIN_MENU_H_

#include "file_dialog.hpp"
#include "image.hpp"

#include "../../vendor/include/glm/glm.hpp"

namespace app {
    void renderMainMenu(FileDialog *file_dialog, Image *img,
                        unsigned int shader, glm::mat4 *proj_mat, const glm::mat4 &view_mat);
}

#endif
