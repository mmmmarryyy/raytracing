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

vec2i get_vec2i_from_string(std::string str, size_t position) {
    vec2i result{};

    size_t new_position;
    result.x = get_int_from_string(str, position, &new_position);
    position += new_position + 1;

    result.y = get_int_from_string(str, position, &new_position);
    return result;
}

vec3f get_vec3f_from_string(std::string str, size_t position) {
    vec3f result{};

    size_t new_position;
    result.x = get_float_from_string(str, position, &new_position);
    position += new_position + 1;

    result.y = get_float_from_string(str, position, &new_position);
    position += new_position + 1;

    result.z = get_float_from_string(str, position, &new_position);
    return result;
}

vec4f get_vec4f_from_string(std::string str, size_t position) {
    vec4f result{};

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
