#include "parse.h"

int get_int_from_string(std::string str, size_t position, size_t *index) {
    return std::stoi(
        str.substr(position, str.find(' ', position) - position), 
        index
    );
}

float get_float_from_string(std::string str, size_t position, size_t *index) {
    return std::stof(
        str.substr(position, str.find(' ', position) - position), 
        index
    );
}

glm::ivec2 get_vec2i_from_string(std::string str, size_t position) {
    glm::ivec2 result{};

    size_t new_position;
    result.x = get_int_from_string(str, position, &new_position);
    position += new_position + 1;

    result.y = get_int_from_string(str, position, &new_position);
    return result;
}

glm::vec3 get_vec3f_from_string(std::string str, size_t position) {
    glm::vec3 result{};

    size_t new_position;
    result.x = get_float_from_string(str, position, &new_position);
    position += new_position + 1;

    result.y = get_float_from_string(str, position, &new_position);
    position += new_position + 1;

    result.z = get_float_from_string(str, position, &new_position);
    return result;
}

glm::quat get_vec4f_from_string(std::string str, size_t position) {
    glm::quat result;

    size_t new_position;
    result.x = get_float_from_string(str, position, &new_position);
    position += new_position + 1;

    result.y = get_float_from_string(str, position, &new_position);
    position += new_position + 1;

    result.z = get_float_from_string(str, position, &new_position);
    position += new_position + 1;

    result.w = get_float_from_string(str, position, &new_position);
    return result;
}
