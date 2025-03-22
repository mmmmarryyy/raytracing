#pragma once

#include "glm.hpp"
 
#include <random>

std::minstd_rand get_random_generator();
glm::vec3 get_random_direction(std::minstd_rand& rng, glm::vec3& normal);
