#pragma once

#include <map>
#include <string>

enum ObjectCommands {
    NEW_PRIMITIVE = 0,
    POSITION = 1,
    ROTATION = 2,
    COLOR = 3,
    PLANE = 4,
    ELLIPSOID = 5,
    BOX = 6,
};

static std::map<ObjectCommands, std::string> object_commands_names = {
    {NEW_PRIMITIVE, "NEW_PRIMITIVE"},
    {POSITION, "POSITION"},
    {ROTATION, "ROTATION"},
    {COLOR, "COLOR"},
    {PLANE, "PLANE"},
    {ELLIPSOID, "ELLIPSOID"},
    {BOX, "BOX"}
};
