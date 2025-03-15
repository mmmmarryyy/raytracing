#pragma once

#include "object.h"

class Plane : public Object {
public:
    Plane(vec3f n) : normal(n) {};

    std::optional<Intersection> is_intersected_by_ray(Ray start_ray) override {
        Ray ray = start_ray.shift_and_rotate_ray(position, rotation);

        float t = - dot(ray.start_position, normal) / dot(ray.direction, normal);

        if (t < 0.0) {
            return std::nullopt;
        }

        Intersection intersection;

        intersection.color = color;
        intersection.normal = rotate(normal, rotation);
        intersection.distance = t;
        if (dot(ray.direction, normal) > 0) {
            intersection.inside_flag = true;
            intersection.normal = -intersection.normal;
        }

        return std::make_optional(intersection);
    };

    vec3f normal;
};
