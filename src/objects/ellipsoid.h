#pragma once

#include <cmath>

class Ellipsoid : public Object {
public:
    Ellipsoid(vec3f r) : radius(r) {};

    std::optional<Intersection> is_intersected_by_ray(Ray start_ray) override {
        Ray ray = start_ray.shift_and_rotate_ray(position, rotation);

        vec3f o_div_radius = ray.start_position / radius;
        vec3f direction_div_radius = ray.direction / radius;

        float a = dot(direction_div_radius, direction_div_radius);
        float b = dot(o_div_radius, direction_div_radius);
        float c = dot(o_div_radius, o_div_radius);

        float discriminant = b * b - a * (c - 1.0);
        
        if (discriminant < 0.0) {
            return std::nullopt;
        }

        discriminant = std::sqrt(discriminant);
        float t1 = (-b - discriminant) / a;
        float t2 = (-b + discriminant) / a;

        if (t2 < 0) {
            return std::nullopt;
        }

        Intersection intersection;
        intersection.color = color;
        intersection.distance = t1;

        if (t1 < 0) {
            intersection.inside_flag = true;
            intersection.distance = t2;
        }

        intersection.normal = get_normal_form((ray.start_position + intersection.distance * ray.direction) / (radius * radius));
        intersection.normal = rotate(intersection.inside_flag ? -intersection.normal : intersection.normal, rotation);

        return std::make_optional(intersection);
    };

    vec3f radius;
};
