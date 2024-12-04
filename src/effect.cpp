#include "include/effect.hpp"

#include <cstring>

void app::Effects::init() {
    memset(m_windows_open, false, sizeof(m_windows_open));
}
