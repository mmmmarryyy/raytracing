#pragma once

#include "vec.h"
 
#include <random>

std::minstd_rand get_random_generator();
vec3f get_random_direction(std::minstd_rand rng);
