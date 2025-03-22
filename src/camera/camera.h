#pragma once

#include "objects/ray.h"
#include "utils/random.h"
#include "glm.hpp"

#include <memory>
#include <cmath>

class Camera {
public:
    Camera() {}

    Ray cast_in_pixel(glm::vec2 p, glm::vec2 random_offset);

    size_t width, height;

    glm::vec3 position;
    glm::vec3 right, up, forward;

    glm::vec2 fov_in_radians;
};