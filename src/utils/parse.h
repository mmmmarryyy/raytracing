#pragma once

#include "glm.hpp"
#include "gtc/quaternion.hpp"

#include <string>

int get_int_from_string(std::string str, size_t position, size_t *index = nullptr);
float get_float_from_string(std::string str, size_t position, size_t *index = nullptr);

glm::ivec2 get_vec2i_from_string(std::string str, size_t position = 0);
glm::vec3 get_vec3f_from_string(std::string str, size_t position = 0);
glm::quat get_vec4f_from_string(std::string str, size_t position = 0);
