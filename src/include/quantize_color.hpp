#ifndef _APP_QUANTIZE_COLORS_H_
#define _APP_QUANTIZE_COLORS_H_

#include <vector>

namespace app {
    enum QuantizePalette {
        GruvboxMaterialDark,
        CatpuccinMocha,
        Nord,
        EverforestDark,
        TomorrowNight,
        QuantizePaletteCount,
    };
    extern std::vector<std::vector<unsigned int>> quantize_colors;
}

#endif
