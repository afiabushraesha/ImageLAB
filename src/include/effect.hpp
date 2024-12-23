#ifndef _APP_EFFECT_H_
#define _APP_EFFECT_H_

#include "../g_engine/include/types.hpp"

#include <cstddef>
#include <vector>

namespace app {
    const size_t EffectCount = 11;

    enum EffectType : unsigned int {
        EffectGrayscaleAverage = 1,
        EffectGrayscaleLumin,
        EffectGrayscaleLight,
        EffectBrightness = 1 << 2,
        EffectTint = 1 << 3,
        EffectContrast = 1 << 4,
        EffectQuantize = 1 << 5,
        EffectNoise = 1 << 6,
        EffectChangeDetect = 1 << 7,
        EffectInvert = 1 << 8,
        EffectThreshold = 1 << 9,
        EffectStegnographyEncode = 1 << 30,
    };

    enum EffectWindowIdx {
        EffectIdxGrayscale = 0,
        EffectIdxBrightness,
        EffectIdxTint,
        EffectIdxContrast,
        EffectIdxQuantize,
        EffectIdxNoise,
        EffectIdxChangeDetect,
        EffectIdxInvert,
        EffectIdxThreshold,
        EffectIdxStegnographyEncode,
        EffectIdxStegnographyDecode,
        EffectIdxCount,
    };

    // TODO: No need for this struct.
    struct EffectUiInfo {
        int m_grayscale_idx = EffectGrayscaleAverage;
    };

    struct EffectProperty {
        EffectUiInfo m_ui_info;
        float m_brightness_multiple = 1.0f;
        float m_tint_color[3] = {1.0f, 1.0f, 1.0f};
        float m_noise_intensity = 0.5f;
        float m_contrast_intensity = 1.0f;
        bool m_is_inverted = false;
        int m_threshold_limit = 127;
        int m_quantize_palette_idx = 0;
    };

    struct Effects {
        unsigned int m_gates = 0;
        unsigned int m_old_gates = 1;
        EffectProperty m_prop;
        bool m_windows_open[EffectIdxCount];

        void init();
        void reset();
    };

    void effectGrayscaleAverageFn(g_engine::vec4<unsigned char> *px);
    void effectGrayscaleLuminFn(g_engine::vec4<unsigned char> *px);
    void effectGrayscaleLightFn(g_engine::vec4<unsigned char> *px);

    void effectBrightnessFn(g_engine::vec4<unsigned char> *px, float multiple);
    void effectTintFn(g_engine::vec4<unsigned char> *px, g_engine::vec3<float> color);
    void effectContrastFn(g_engine::vec4<unsigned char> *px,
                          g_engine::vec3<unsigned char> min_intensity,
                          g_engine::vec3<unsigned char> max_intensity);

    void effectQuantizeFn(g_engine::vec4<unsigned char> *px,
                          const std::vector<unsigned int> &color_set);
    void effectNoiseFn(g_engine::vec4<unsigned char> *px, g_engine::vec2<int> px_coords,
                       g_engine::vec2<int> image_size, float intensity);
    void effectChangeDetectFn(g_engine::vec4<unsigned char> *px);

    void effectInvertFn(g_engine::vec4<unsigned char> *px);
    void effectThresholdFn(g_engine::vec4<unsigned char> *px, unsigned int threshold);
}

#endif
