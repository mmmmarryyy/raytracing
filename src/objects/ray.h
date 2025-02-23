#pragma once

#include "utils/vec.h"

class Ray {
public:
    Ray(vec3f position, vec3f d) : start_position(position), direction(d) {
        normal(direction);
    }

    Ray shift_and_rotate_ray(vec3f position, vec4f rotation) {
        Ray ray = Ray(start_position, direction);

        ray.start_position.x -= position.x;
        ray.start_position.y -= position.y;
        ray.start_position.z -= position.z;

        ray.start_position = rotate(ray.start_position, -rotation);
        ray.direction = rotate(ray.direction, -rotation);

        return ray;
    }

    vec3f start_position;
    vec3f direction;
};
