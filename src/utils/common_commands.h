#pragma once

#include <map>
#include <string>

enum CommonCommands {
    DIMENSIONS = 0,
    BG_COLOR = 1,
    CAMERA_POSITION = 2,
    CAMERA_RIGHT = 3,
    CAMERA_UP = 4,
    CAMERA_FORWARD = 5,
    CAMERA_FOV_X = 6,
    RAY_DEPTH = 7,
    AMBIENT_LIGHT = 8,
    SAMPLES = 9,
};

static std::map<CommonCommands, std::string> common_commands_names = {
    {DIMENSIONS, "DIMENSIONS"},
    {BG_COLOR, "BG_COLOR"},
    {CAMERA_POSITION, "CAMERA_POSITION"},
    {CAMERA_RIGHT, "CAMERA_RIGHT"},
    {CAMERA_UP, "CAMERA_UP"},
    {CAMERA_FORWARD, "CAMERA_FORWARD"},
    {CAMERA_FOV_X, "CAMERA_FOV_X"},
    {RAY_DEPTH, "RAY_DEPTH"},
    {AMBIENT_LIGHT, "AMBIENT_LIGHT"},
    {SAMPLES, "SAMPLES"},
};
