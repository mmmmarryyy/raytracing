#include "camera.h"

Ray Camera::cast_in_pixel(glm::vec2 p, glm::vec2 random_offset) {
    glm::vec3 t{};

    t[0] = (2.0 * ((float)p.x + random_offset.x) / (float)width - 1.0) * fov_in_radians.x;
    t[1] = -(2.0 * ((float)p.y + random_offset.y) / (float)height - 1.0) * fov_in_radians.y;
    t[2] = 1;

    glm::vec3 direction{};
    direction = direction + t.x * right;
    direction = direction + t.y * up;
    direction = direction + t.z * forward;

    return {position, glm::normalize(direction)};
}