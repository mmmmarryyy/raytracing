#include "color.h"

uint8_t normal_to_rgb(float val) {
    return std::round(clamp(val * 255, 0.0, 255.0));
}

vec3ui normal_to_rgb(vec3f val) {
    vec3ui result{};
    result.x = normal_to_rgb(val.x);
    result.y = normal_to_rgb(val.y);
    result.z = normal_to_rgb(val.z);
    return result;
}

float rgb_to_normal(int val) {
    return (float)val / 255.0;
}

vec3f rgb_to_normal(vec3ui val) {
    vec3f result{};
    result.x = rgb_to_normal(val.x);
    result.y = rgb_to_normal(val.y);
    result.z = rgb_to_normal(val.z);
    return result;
}
