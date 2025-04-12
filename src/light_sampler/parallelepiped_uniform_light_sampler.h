#pragma once

#include "light_sampler.h"
#include "objects/box.h"
#include "glm.hpp"

#include <memory>
#include <random>
 
struct ParallelepipedUniform : LightSampler {
    ParallelepipedUniform(std::shared_ptr<Box> &box) : parallelepiped(box) {
        w = 4.0 * glm::dvec3 {
            box->size.y * box->size.z, 
            box->size.x * box->size.z, 
            box->size.x * box->size.y
        };
    };

    glm::dvec3 sample(glm::dvec3 &position, glm::dvec3 &normal, std::minstd_rand &random_generator) override {
        double u = get_random_double(random_generator, 0.0, 2.0 * (w.x + w.y + w.z));
    
        glm::dvec3 sample_result;
        if (u < w.x) {
            sample_result = {
                parallelepiped->size.x, 
                get_random_double(random_generator, -1.0, 1.0) * parallelepiped->size.y, 
                get_random_double(random_generator, -1.0, 1.0) * parallelepiped->size.z
            };
        } else if (u < 2 * w.x) {
            sample_result = {
                -parallelepiped->size.x, 
                get_random_double(random_generator, -1.0, 1.0) * parallelepiped->size.y, 
                get_random_double(random_generator, -1.0, 1.0) * parallelepiped->size.z
            };
        } else if (u < 2 * w.x + w.y) {
            sample_result = {
                get_random_double(random_generator, -1.0, 1.0) * parallelepiped->size.x, 
                parallelepiped->size.y, 
                get_random_double(random_generator, -1.0, 1.0) * parallelepiped->size.z
            };
        } else if (u < 2 * (w.x + w.y)) {
            sample_result = {
                get_random_double(random_generator, -1.0, 1.0) * parallelepiped->size.x, 
                -parallelepiped->size.y, 
                get_random_double(random_generator, -1.0, 1.0) * parallelepiped->size.z
            };
        } else if (u < 2 * (w.x + w.y) + w.z) {
            sample_result = {
                get_random_double(random_generator, -1.0, 1.0) * parallelepiped->size.x, 
                get_random_double(random_generator, -1.0, 1.0) * parallelepiped->size.y, 
                parallelepiped->size.z
            };
        } else {
            sample_result = {
                get_random_double(random_generator, -1.0, 1.0) * parallelepiped->size.x, 
                get_random_double(random_generator, -1.0, 1.0) * parallelepiped->size.y,
                -parallelepiped->size.z
            };
        }
    
        my_rotate(parallelepiped->rotation, sample_result);
        return glm::normalize(sample_result + parallelepiped->position - position);
    };

    double pdf(glm::dvec3 &position, glm::dvec3 &normal, glm::dvec3 &direction) override {
        Ray ray{position, direction};
        double sample_result = 0.0;
    
        std::optional<Intersection> optional_intersection = parallelepiped->is_intersected_by_ray(ray);
        Intersection intersection;
        if (optional_intersection.has_value()) {
            intersection = optional_intersection.value();
        }
        
        if (intersection.distance < std::numeric_limits<double>::max()) {
            glm::dvec3 y = position + direction * (intersection.distance + 1e-4);
            sample_result += 1.0 / (2.0 * (w.x + w.y + w.z)) * glm::length(position - y) * glm::length(position - y) / std::abs(glm::dot(intersection.normal, glm::normalize(position - y)));
            ray.start_position = y;
            optional_intersection = parallelepiped->is_intersected_by_ray(ray);
            if (optional_intersection.has_value()) {
                intersection = optional_intersection.value();
            } else {
                intersection = {};
            }
            if (intersection.distance < std::numeric_limits<double>::max()) {
                y = ray.start_position + direction * intersection.distance;
                sample_result += 1.0 / (2.0 * (w.x + w.y + w.z)) * glm::length(position - y) * glm::length(position - y) / std::abs(glm::dot(intersection.normal, glm::normalize(position - y)));
            }
        }
    
        return sample_result;
    };

private:
    std::shared_ptr<Box> parallelepiped;
    glm::dvec3 w;

    void my_rotate(glm::dquat q, glm::dvec3 &v) {
        glm::dvec3 t = 2.0 * glm::cross({q[1], q[2], q[3]}, v);
        v = v + q[0] * t + cross({q[1], q[2], q[3]}, t);
    }
};