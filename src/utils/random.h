#pragma once

#include "glm.hpp"
 
#include <random>

std::minstd_rand get_random_generator();
double get_random_double(std::minstd_rand& rng, double from, double to);
uint32_t get_random_uint(std::minstd_rand& rng, uint32_t to);
glm::dvec3 random_direction_helper(std::minstd_rand& rng);
glm::dvec3 get_random_direction(std::minstd_rand& rng, glm::dvec3& normal);
