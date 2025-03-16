#pragma once

#include "utils/vec.h"
#include "utils/parse.h"
#include "utils/object_commands.h"
#include "ray.h"
#include "intersection.h"

#include <fstream>
#include <optional>

class Object {
public:
    vec3f position = {0.0, 0.0, 0.0};
    vec3f color = {0.0, 0.0, 0.0};
    vec4f rotation = {0.0, 0.0, 0.0, 1.0};
    vec3f emission = {0.0, 0.0, 0.0};

    enum Material {
        Diffuse,
        Dielectric,
        Metallic
    };

    Material material = Diffuse;
    float ior = 1.0;

    virtual std::optional<Intersection> is_intersected_by_ray(Ray ray) = 0;

    void parse(const std::string& line) {
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
            color = get_vec3f_from_string(line, space_position + 1);
        } else if (command == object_commands_names[METALLIC]) {
            material = Metallic;
        } else if (command == object_commands_names[DIELECTRIC]) {
            material = Dielectric;
        } else if (command == object_commands_names[IOR]) {
            ior = get_float_from_string(line, space_position + 1);
        } else if (command == object_commands_names[EMISSION]) {
            emission = get_vec3f_from_string(line, space_position + 1);
        } 
        // USE THIS COMMENTED BLOCK TO DEBUG; FORBIDDEN TO DELETE
        // else {
        //     std::cout << "DEBUG: Find unknown command = " << command << " while parsing object" << std::endl;
        // }
    };
};
