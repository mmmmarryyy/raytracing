#pragma once


#include "glm.hpp"

#include <cmath>

uint8_t normal_to_rgb(float val);
glm::vec3 normal_to_rgb(glm::vec3 val);

float rgb_to_normal(int val);
glm::vec3 rgb_to_normal(glm::vec3 val);

glm::vec3 saturate(const glm::vec3 &color);
glm::vec3 aces_tonemap(const glm::vec3 &x);
