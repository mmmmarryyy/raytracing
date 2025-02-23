#pragma once

#include "utils/vec.h"
#include "utils/parse.h"
#include "utils/object_commands.h"
#include "ray.h"

#include <fstream>
#include <optional>

class Object {
public:
    vec3f position = {0, 0, 0};
    vec4f rotation = {0, 0, 0, 1};

    vec3f color = {};

    virtual std::optional<float> is_intersected_by_ray(Ray ray) = 0;

    virtual void parse(std::ifstream &in) {
        std::string line;
        int parse_stages = 0;

        bool color_flag = false;

        while (std::getline(in, line)) {
            std::string command;
            size_t space_position = line.find(' ');

            if (space_position == std::string::npos) {
                command = line;
            } else {
                command = line.substr(0, space_position);
            }

            if (command == object_commands_names[POSITION]) {
                position = get_vec3f_from_string(line, space_position + 1);
            } else if (command == object_commands_names[ROTATION]) {
                rotation = get_normal_form(get_vec4f_from_string(line, space_position + 1));
            } else if (command == object_commands_names[COLOR]) {
                color_flag = true;
                color = get_vec3f_from_string(line, space_position + 1);
            } else if (command == object_commands_names[NEW_PRIMITIVE]) {
                break;
            }
        }

        if (!color_flag) {
            throw std::runtime_error("Invalid scene: field COLOR is missing");
        }
    };
};
