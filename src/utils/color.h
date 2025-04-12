#pragma once


#include "glm.hpp"

#include <cmath>

uint8_t normal_to_rgb(double val);
glm::dvec3 normal_to_rgb(glm::dvec3 val);

double rgb_to_normal(int val);
glm::dvec3 rgb_to_normal(glm::dvec3 val);

glm::dvec3 saturate(const glm::dvec3 &color);
glm::dvec3 aces_tonemap(const glm::dvec3 &x);
