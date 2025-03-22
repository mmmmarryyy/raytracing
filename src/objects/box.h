#pragma once

#include "object.h"

class Box : public Object {
public:
    Box(glm::vec3 s): size(s) {};

    std::optional<Intersection> is_intersected_by_ray(Ray start_ray) override {
        Ray ray = start_ray.shift_and_rotate_ray(position, inversed_rotation);
        ray.depth = start_ray.depth;
        
        glm::vec3 t1 = (-size - ray.start_position) / ray.direction;
        glm::vec3 t2 = (size - ray.start_position) / ray.direction;
        
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
    
        Intersection intersection;
        intersection.distance = t1_max;
        if (t1_max < 0) {
            intersection.distance = t2_min;
        }

        glm::vec3 intersection_normal = (ray.start_position + intersection.distance * ray.direction) / size;
        
        for (std::size_t i = 0; i < 3; i++) {
            if (std::abs(std::abs(intersection_normal[i]) - 1.0) < 1e-5) {
                intersection_normal[i] = (intersection_normal[i] > 0.0) ? 1.0 : -1.0;
            } else {
                intersection_normal[i] = 0;
            }
        }

        intersection.inside_flag = glm::dot(intersection_normal, ray.direction) > 0;
        if (intersection.inside_flag) {
            intersection_normal = -intersection_normal;
        }

        my_rotate(rotation, intersection_normal);
        intersection.normal = intersection_normal;
        return std::make_optional(intersection);
    };

    glm::vec3 size;
};
