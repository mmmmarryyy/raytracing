#pragma once

#include "vec.h"

#include <string>

int get_int_from_string(std::string str, size_t position, size_t *index = nullptr);
float get_float_from_string(std::string str, size_t position, size_t *index = nullptr);

vec2i get_vec2i_from_string(std::string str, size_t position = 0);
vec3f get_vec3f_from_string(std::string str, size_t position = 0);
vec4f get_vec4f_from_string(std::string str, size_t position = 0);
