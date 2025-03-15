#pragma once

#include <fstream>
#include <string>
#include <iostream>

#include "utils/vec.h"
#include "utils/light_commands.h"
#include "utils/parse.h"

class LightSource {
public:
    enum LightType {
        Directional,
        Positional
    };

    vec3f intensity = {0.0, 0.0, 0.0};
    vec3f direction = {0.0, 0.0, 0.0};
    vec3f position = {0.0, 0.0, 0.0};
    vec3f attenuation = {0.0, 0.0, 0.0};

    LightType light_type;

    void parse(const std::string& line) {
        size_t space_position = line.find(' ');
        if (space_position == std::string::npos) {
            return;
        }

        std::string command = line.substr(0, space_position);

        if (command == light_commands_names[LIGHT_INTENSITY]) {
            intensity = get_vec3f_from_string(line, space_position + 1);
        } else if (command == light_commands_names[LIGHT_DIRECTION]) {
            light_type = Directional;
            direction = get_normal_form(get_vec3f_from_string(line, space_position + 1));
        } else if (command == light_commands_names[LIGHT_POSITION]) {
            light_type = Positional;
            position = get_vec3f_from_string(line, space_position + 1);
        } else if (command == light_commands_names[LIGHT_ATTENUATION]) {
            light_type = Positional;
            attenuation = get_vec3f_from_string(line, space_position + 1);
        } 
        // USE THIS COMMENTED BLOCK TO DEBUG; FORBIDDEN TO DELETE
        // else {
        //     std::cout << "DEBUG: Find unknown command = " << command << " while parsing lights" << std::endl;
        // }
    };
};
