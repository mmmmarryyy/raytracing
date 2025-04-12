#pragma once

#include "objects/ray.h"
#include "utils/random.h"
#include "glm.hpp"

#include <memory>
#include <cmath>

class Camera {
public:
    Camera() {}

    Ray cast_in_pixel(glm::dvec2 p, glm::dvec2 random_offset);

    size_t width, height;

    glm::dvec3 position;
    glm::dvec3 right, up, forward;

    glm::dvec2 fov_in_radians;
};