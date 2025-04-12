#include "camera.h"

Ray Camera::cast_in_pixel(glm::dvec2 p, glm::dvec2 random_offset) {
    glm::dvec3 t{};

    t[0] = (2.0 * (p.x + random_offset.x) / (double)width - 1.0) * fov_in_radians.x;
    t[1] = -(2.0 * (p.y + random_offset.y) / (double)height - 1.0) * fov_in_radians.y;
    t[2] = 1;

    glm::dvec3 direction{};
    direction = direction + t.x * right;
    direction = direction + t.y * up;
    direction = direction + t.z * forward;

    return {position, glm::normalize(direction)};
}