#pragma once

class Ellipsoid : public Object {
public:
    Ellipsoid(vec3f r) : radius(r) {};

    std::optional<float> is_intersected_by_ray(Ray start_ray) override {
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

        if (t1 < 0) {
            t1 = t2;
        }
        return std::make_optional(t1);
    };

    vec3f radius;
};
