#pragma once
 
#include "light_sampler.h"
#include "objects/ellipsoid.h"
#include "glm.hpp"

#include <memory>

struct EllipsoidLightSampler : LightSampler {
    EllipsoidLightSampler(std::shared_ptr<Ellipsoid> &object) : ellipsoid(object) {
        square_radius = {
            ellipsoid->radius.y * ellipsoid->radius.z, 
            ellipsoid->radius.x * ellipsoid->radius.z,
            ellipsoid->radius.x * ellipsoid->radius.y
        };
        square_radius *= square_radius;
    };

    glm::dvec3 sample(glm::dvec3 &position, glm::dvec3 &normal, std::minstd_rand &random_generator) override {
        glm::dvec3 vec = ellipsoid->radius * random_direction_helper(random_generator);
        my_rotate(ellipsoid->rotation, vec);
        return glm::normalize(vec + ellipsoid->position - position);
    };

    double pdf(glm::dvec3 &position, glm::dvec3 &normal, glm::dvec3 &direction) override {
        Ray ray{position, direction};
        double pdf_result = 0.0;
    
        std::optional<Intersection> optional_intersection = ellipsoid->is_intersected_by_ray(ray);
        Intersection intersection;
        if (optional_intersection.has_value()) {
            intersection = optional_intersection.value();
        }
        
        if (intersection.distance < std::numeric_limits<double>::max()) {
            glm::dvec3 y = position + direction * (intersection.distance + 1e-4);
            glm::dvec3 point_on_sphere = y - ellipsoid->position;
            my_rotate(ellipsoid->inversed_rotation, point_on_sphere);
            glm::dvec3 square_normal = point_on_sphere * point_on_sphere / ellipsoid->radius / ellipsoid->radius;
            pdf_result += glm::length(position - y) * glm::length(position - y) / std::abs(glm::dot(intersection.normal, glm::normalize(position - y))) / 4.0 / M_PI / sqrt(glm::dot(square_normal, square_radius));
            
            ray.start_position = y;
            optional_intersection = ellipsoid->is_intersected_by_ray(ray);
            if (optional_intersection.has_value()) {
                intersection = optional_intersection.value();
            } else {
                intersection = {};
            }
            if (intersection.distance < std::numeric_limits<double>::max()) {
                y = ray.start_position + direction * intersection.distance;
                point_on_sphere = y - ellipsoid->position;
                my_rotate(ellipsoid->inversed_rotation, point_on_sphere);
                square_normal = point_on_sphere * point_on_sphere / ellipsoid->radius / ellipsoid->radius;
                pdf_result += glm::length(position - y) * glm::length(position - y) / std::abs(glm::dot(intersection.normal, glm::normalize(position - y))) / 4.0 / M_PI / sqrt(glm::dot(square_normal, square_radius));
            }
        }
    
        return pdf_result;
    };

private:
    std::shared_ptr<Ellipsoid> ellipsoid;
    glm::dvec3 square_radius;

    void my_rotate(glm::dquat q, glm::dvec3 &v) {
        glm::dvec3 t = 2.0 * glm::cross({q[1], q[2], q[3]}, v);
        v = v + q[0] * t + cross({q[1], q[2], q[3]}, t);
    }
};