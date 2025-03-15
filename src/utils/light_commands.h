#pragma once

#include <map>
#include <string>

enum LightCommands {
    NEW_LIGHT = 0,
    LIGHT_INTENSITY = 1,
    LIGHT_DIRECTION = 2,
    LIGHT_POSITION = 3,
    LIGHT_ATTENUATION = 4,
};

static std::map<LightCommands, std::string> light_commands_names = {
    {NEW_LIGHT, "NEW_LIGHT"},
    {LIGHT_INTENSITY, "LIGHT_INTENSITY"},
    {LIGHT_DIRECTION, "LIGHT_DIRECTION"},
    {LIGHT_POSITION, "LIGHT_POSITION"},
    {LIGHT_ATTENUATION, "LIGHT_ATTENUATION"},
};
