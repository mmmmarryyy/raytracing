#pragma once

#include "object.h"

class Plane : public Object {
public:
    Plane(glm::dvec3 n) : normal(n) {};

    std::optional<Intersection> is_intersected_by_ray(Ray start_ray) override {
        Ray ray = start_ray.shift_and_rotate_ray(position, rotation);
        ray.depth = start_ray.depth;

        double t = - glm::dot(ray.start_position, normal) / glm::dot(ray.direction, normal);

        if (t < 0.0) {
            return std::nullopt;
        }

        Intersection intersection;

        intersection.normal = normal;
        intersection.distance = t;
        if (glm::dot(ray.direction, normal) > 0) {
            intersection.inside_flag = true;
            intersection.normal = -intersection.normal;
        }
        my_rotate(rotation, intersection.normal);
        intersection.normal = glm::normalize(intersection.normal);

        return std::make_optional(intersection);
    };

    glm::dvec3 normal;
};
