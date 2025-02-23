#include "camera.h"

Ray Camera::cast_in_pixel(vec2i p) {
    vec3f t{};
    
    t.x = (2.0 * ((float)p.x + 0.5) / (float)width - 1.0) * std::tan(fov_in_radians.x / 2.0);
    t.y = -(2.0 * ((float)p.y + 0.5) / (float)height - 1.0) * std::tan(fov_in_radians.y / 2.0);
    t.z = 1;

    vec3f direction{};
    direction = direction + t.x * right;
    direction = direction + t.y * up;
    direction = direction + t.z * forward;

    return {position, direction};
}