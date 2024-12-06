#version 330

out vec4 out_color;
in vec2 v_texture_coords;

uniform sampler2D image_texture;

// variables because enums doesn't exist.
const uint EffectGrayscaleAverage = 1u;
const uint EffectGrayscaleLumin = 2u;
const uint EffectGrayscaleLight = 3u;
const uint EffectBrightness = 1u << 2;
const uint EffectTint = 1u << 3;
const uint EffectContrast = 1u << 4;
const uint EffectQuantize = 1u << 5;
const uint EffectNoise = 1u << 6;
const uint EffectChangeDetect = 1u << 7;
const uint EffectInvert = 1u << 8;
const uint EffectThreshold = 1u << 9;

uniform uint effect_gates;
uniform vec3 tint_color;
uniform float brightness_multiple;
uniform float noise_intensity;
uniform float contrast_intensity;
uniform uint threshold_limit;
uniform uvec3 max_intensity;
uniform uvec3 min_intensity;

vec4 grayscaleAverage(vec4 px) {
    float y = (px.r + px.g + px.b) / 3.0f;
    return vec4(y, y, y, px.a);
}

vec4 grayscaleLumin(vec4 px) {
    float y = (0.299f * px.r) + (0.587f * px.g) + (0.114f * px.b);
    return vec4(y, y, y, px.a);
}

vec4 grayscaleLightness(vec4 px) {
    float y = (min(px.r, min(px.g, px.b)) + max(px.r, max(px.g, px.b))) / 2.0f;
    return vec4(y, y, y, px.a);
}

vec4 brightness(vec4 px, float multiple) {
    return vec4(px.rgb * vec3(multiple), px.a);
}

vec4 tint(vec4 px, vec3 color) {
    return vec4(px.rgb * color, px.a);
}

vec4 invert(vec4 px) {
    return vec4(vec3(1.0f) - px.rgb, px.a);
}

vec4 threshold(vec4 px, float limit) {
    vec4 _px = grayscaleLumin(px);
    if (_px.r > limit) return vec4(1.0f);
    else return vec4(vec3(0.0f), 1.0f);
}

vec4 contrast(vec4 px) {
    return vec4(
        ((px.r * 255) - min_intensity.r) / (max_intensity.r - min_intensity.r),
        ((px.g * 255) - min_intensity.g) / (max_intensity.g - min_intensity.g),
        ((px.b * 255) - min_intensity.b) / (max_intensity.b - min_intensity.b),
        px.a
    );
}

void main() {
    vec4 pixel_color = texture(image_texture, v_texture_coords);

    if ((effect_gates & 3u) == EffectGrayscaleAverage) {
        pixel_color = grayscaleAverage(pixel_color);
    } else if ((effect_gates & 3u) == EffectGrayscaleLumin) {
        pixel_color = grayscaleLumin(pixel_color);
    } else if ((effect_gates & 3u) == EffectGrayscaleLight) {
        pixel_color = grayscaleLightness(pixel_color);
    }

    if ((effect_gates & EffectBrightness) == EffectBrightness) {
        pixel_color = brightness(pixel_color, brightness_multiple);
    }
    if ((effect_gates & EffectTint) == EffectTint) {
        pixel_color = tint(pixel_color, tint_color);
    }
    if ((effect_gates & EffectInvert) == EffectInvert) {
        pixel_color = invert(pixel_color);
    }
    if ((effect_gates & EffectThreshold) == EffectThreshold) {
        pixel_color = threshold(pixel_color, threshold_limit / 255.0f);
    }
    if ((effect_gates & EffectContrast) == EffectContrast) {
        pixel_color = contrast(pixel_color);
    }

    out_color = pixel_color;
}
