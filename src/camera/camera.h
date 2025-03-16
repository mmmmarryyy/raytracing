#pragma once

#include "utils/vec.h"
#include "objects/ray.h"

#include <memory>
#include <cmath>

class Camera {
public:
    Camera() {}

    Ray cast_in_pixel(vec2i position, vec2f random_offset = {});

    size_t width, height;

    vec3f position;
    vec3f right, up, forward;

    vec2f fov_in_radians;
};