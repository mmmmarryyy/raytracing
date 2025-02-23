#pragma once

#include "object.h"

class Box : public Object {
public:
    Box(vec3f s): size(s) {};

    std::optional<float> is_intersected_by_ray(Ray start_ray) override {
        Ray ray = start_ray.shift_and_rotate_ray(position, rotation);

        vec3f t1{};
        vec3f t2{};

        t1.x = (-size.x - ray.start_position.x) / ray.direction.x;
        t2.x = (size.x - ray.start_position.x) / ray.direction.x;

        t1.y = (-size.y - ray.start_position.y) / ray.direction.y;
        t2.y = (size.y - ray.start_position.y) / ray.direction.y;

        t1.z = (-size.z - ray.start_position.z) / ray.direction.z;
        t2.z = (size.z - ray.start_position.z) / ray.direction.z;
        
        if (t1.x > t2.x) {
            std::swap(t1.x, t2.x);
        }
        if (t1.y > t2.y) {
            std::swap(t1.y, t2.y);
        }
        if (t1.z > t2.z) {
            std::swap(t1.z, t2.z);
        }

        float t1_max = std::max(std::max(t1.x, t1.y), t1.z);
        float t2_min = std::min(std::min(t2.x, t2.y), t2.z);

        if (t1_max > t2_min || t2_min < 0) {
            return std::nullopt;
        }

        if (t1_max < 0) {
            t1_max = t2_min;
        }

        return std::make_optional(t1_max);
    };

    vec3f size;
};
