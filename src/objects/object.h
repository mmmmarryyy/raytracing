#pragma once

#include "utils/parse.h"
#include "utils/object_commands.h"
#include "ray.h"
#include "intersection.h"
#include "gtc/quaternion.hpp"
#include "glm.hpp"

#include <fstream>
#include <optional>

class Object {
public:
    glm::vec3 position = {0.0, 0.0, 0.0};
    glm::vec3 color = {0.0, 0.0, 0.0};
    glm::quat rotation = {1.0, 0.0, 0.0, 0.0};
    glm::quat inversed_rotation = {1.0, 0.0, 0.0, 0.0};
    glm::vec3 emission = {0.0, 0.0, 0.0};

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
            rotation = get_vec4f_from_string(line, space_position + 1);
            inversed_rotation = glm::conjugate(rotation);
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

protected:
    void my_rotate(glm::quat q, glm::vec3 &v) {
        glm::vec3 t = 2.f * glm::cross({q[1], q[2], q[3]}, v);
        v = v + q[0] * t + cross({q[1], q[2], q[3]}, t);
    }
};
