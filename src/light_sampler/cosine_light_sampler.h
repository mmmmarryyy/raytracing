#pragma once

#include "light_sampler.h"
#include "glm.hpp"
 
struct CosineLightSampler : LightSampler {
    glm::dvec3 sample(glm::dvec3 &position, glm::dvec3 &normal, std::minstd_rand &random_generator) override {
        return glm::normalize(random_direction_helper(random_generator) + normal);
    };

    double pdf(glm::dvec3 &position, glm::dvec3 &normal, glm::dvec3 &direction) override {
        if (glm::dot(direction, normal) < 0) {
            return 0;
        } else {
            return glm::dot(direction, normal) / M_PI;
        }
    };
};