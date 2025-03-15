#pragma once

#include "utils/vec.h"

typedef struct {
    float distance;
    vec3f normal, color;
    bool inside_flag = false;
} Intersection;