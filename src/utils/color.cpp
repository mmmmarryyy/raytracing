#include "color.h"

uint8_t normal_to_rgb(float val) {
    return std::round(glm::clamp(val * 255.0, 0.0, 255.0));
}

glm::vec3 normal_to_rgb(glm::vec3 val) {
    glm::vec3 result{};
    result.x = normal_to_rgb(val.x);
    result.y = normal_to_rgb(val.y);
    result.z = normal_to_rgb(val.z);
    return result;
}

float rgb_to_normal(int val) {
    return (float)val / 255.0;
}

glm::vec3 rgb_to_normal(glm::vec3 val) {
    glm::vec3 result{};
    result.x = rgb_to_normal(val.x);
    result.y = rgb_to_normal(val.y);
    result.z = rgb_to_normal(val.z);
    return result;
}

glm::vec3 saturate(const glm::vec3 &color) {
    return glm::clamp(color, glm::vec3(0.0), glm::vec3(1.0));
}

glm::vec3 aces_tonemap(const glm::vec3 &x) {
    const float a = 2.51f;
    const float b = 0.03f;
    const float c = 2.43f;
    const float d = 0.59f;
    const float e = 0.14f;
    return saturate((x * (a * x + b)) / (x * (c * x + d) + e));
}
