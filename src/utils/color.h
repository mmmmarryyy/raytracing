#pragma once

#include "vec.h"

#include <cmath>

uint8_t normal_to_rgb(float val);
vec3ui normal_to_rgb(vec3f val);

float rgb_to_normal(int val);
vec3f rgb_to_normal(vec3ui val);
