#pragma once

#include "light_sampler.h"
#include "glm.hpp"

#include <memory>

struct MixLightSampler : LightSampler {
public:
    MixLightSampler(std::vector<std::unique_ptr<LightSampler>> &&samplers) {
        light_samplers = std::move(samplers);
    }

    glm::dvec3 sample(glm::dvec3 &position, glm::dvec3 &normal, std::minstd_rand &random_generator) override {
        index = get_random_uint(random_generator, light_samplers.size());
        return light_samplers[index]->sample(position, normal, random_generator);
    };

    double pdf(glm::dvec3 &position, glm::dvec3 &normal, glm::dvec3 &direction) override {
        double pdf_helper = 0.0;
        for (std::unique_ptr<LightSampler> &sampler: light_samplers) {
            pdf_helper += sampler->pdf(position, normal, direction);
        }
        return pdf_helper / light_samplers.size();
    };

private:
    std::vector<std::unique_ptr<LightSampler>> light_samplers;
    uint32_t index;
};