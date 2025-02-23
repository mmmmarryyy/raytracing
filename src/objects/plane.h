#pragma once

#include "object.h"

class Plane : public Object {
public:
    Plane(vec3f n) : normal(n) {};

    std::optional<float> is_intersected_by_ray(Ray start_ray) override {
        Ray ray = start_ray.shift_and_rotate_ray(position, rotation);

        float t = - dot(ray.start_position, normal) / dot(ray.direction, normal);

        if (t < 0.0) {
            return std::nullopt;
        }

        return std::make_optional(t);
    };

    vec3f normal;
};
