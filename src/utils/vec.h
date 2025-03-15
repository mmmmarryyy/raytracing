#pragma once

#include <cstdint>
#include <cmath>
#include <algorithm>
#include <string>

struct vec2i {
    int x;
    int y;
};

struct vec2f {
    float x;
    float y;
};

struct vec3ui {
    uint8_t x;
    uint8_t y;
    uint8_t z;
};

struct vec3f {
    float x;
    float y;
    float z;

    vec3f &operator+=(vec3f other_vec);
    vec3f &operator*=(vec3f other_vec);
    vec3f &operator*=(float other_vec);
};

struct vec4f {
    float x;
    float y;
    float z;
    float w;
};

float length(vec2f vec);
float length(vec3f vec);
float length(vec4f vec);

vec2f get_normal_form(vec2f vec);
vec3f get_normal_form(vec3f vec);
vec4f get_normal_form(vec4f vec);

void normal(vec2f &vec);
void normal(vec3f &vec);
void normal(vec4f &vec);

float dot(vec3f vec1, vec3f vec2);
vec3f cross(vec3f vec1, vec3f vec2);
vec3f pow(vec3f vec, float power);

vec3f operator+(vec3f vec, float t);
vec3f operator+(vec3f vec1, vec3f vec2);
vec3f operator-(vec3f vec);
vec3f operator-(vec3f vec1, vec3f vec2);
vec3f operator*(vec3f vec, float t);
vec3f operator*(float t, vec3f vec);
vec3f operator*(vec3f vec1, vec3f vec2);
vec3f operator/(vec3f vec1, vec3f vec2);
vec4f operator-(vec4f quart);

vec3f rotate(vec3f vec, vec4f quart);
vec3f rotate(vec3f vec, vec3f axis, float angle);

float clamp(float vec, float min, float max);
vec3f clamp(vec3f vec, vec3f min, vec3f max);

vec3f aces_tonemap(const vec3f &x);
