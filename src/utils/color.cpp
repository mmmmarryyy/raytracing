#include "color.h"

uint8_t normal_to_rgb(double val) {
    return std::round(glm::clamp(val * 255.0, 0.0, 255.0));
}

glm::dvec3 normal_to_rgb(glm::dvec3 val) {
    glm::dvec3 result{};
    result.x = normal_to_rgb(val.x);
    result.y = normal_to_rgb(val.y);
    result.z = normal_to_rgb(val.z);
    return result;
}

double rgb_to_normal(int val) {
    return (double)val / 255.0;
}

glm::dvec3 rgb_to_normal(glm::dvec3 val) {
    glm::dvec3 result{};
    result.x = rgb_to_normal(val.x);
    result.y = rgb_to_normal(val.y);
    result.z = rgb_to_normal(val.z);
    return result;
}

glm::dvec3 saturate(const glm::dvec3 &color) {
    return glm::clamp(color, glm::dvec3(0.0), glm::dvec3(1.0));
}

glm::dvec3 aces_tonemap(const glm::dvec3 &x) {
    const double a = 2.51f;
    const double b = 0.03f;
    const double c = 2.43f;
    const double d = 0.59f;
    const double e = 0.14f;
    return saturate((x * (a * x + b)) / (x * (c * x + d) + e));
}
