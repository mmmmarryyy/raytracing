#pragma once

#include <cmath>

class Ellipsoid : public Object {
public:
    Ellipsoid(glm::dvec3 r) : radius(r) {};

    std::optional<Intersection> is_intersected_by_ray(Ray start_ray) override {
        Ray ray = start_ray.shift_and_rotate_ray(position, inversed_rotation);
        ray.depth = start_ray.depth;

        glm::dvec3 o_div_radius = ray.start_position / radius;
        glm::dvec3 direction_div_radius = ray.direction / radius;

        double a = glm::dot(direction_div_radius, direction_div_radius);
        double b = glm::dot(o_div_radius, direction_div_radius);
        double c = glm::dot(o_div_radius, o_div_radius) ;

        double discriminant = b * b - a * (c - 1.0);
        
        if (discriminant < 0.0) {
            return std::nullopt;
        }

        discriminant = std::sqrt(discriminant);
        double t1 = (-b - discriminant) / a;
        double t2 = (-b + discriminant) / a;

        if (t2 < 0) {
            return std::nullopt;
        }

        Intersection intersection;
        intersection.distance = t1;
        if (t1 < 0) {
            intersection.distance = t2;
        }

        intersection.normal = (ray.start_position + intersection.distance * ray.direction) / (radius * radius);
        intersection.inside_flag = glm::dot(intersection.normal, ray.direction) > 0;

        if (intersection.inside_flag) {
            intersection.normal *= -1;
        }
        my_rotate(rotation, intersection.normal);
        intersection.normal = glm::normalize(intersection.normal);

        return std::make_optional(intersection);
    };

    glm::dvec3 radius;
};
