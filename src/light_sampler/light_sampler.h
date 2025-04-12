#pragma once
 
#include "utils/random.h"
#include "objects/intersection.h"
#include "glm.hpp"
 
struct LightSampler {
public:
    virtual glm::dvec3 sample(glm::dvec3 &position, glm::dvec3 &normal, std::minstd_rand & random_generator) = 0;
    virtual double pdf(glm::dvec3 &position, glm::dvec3 &normal, glm::dvec3 &direction) = 0;
    virtual ~LightSampler() = default;
};