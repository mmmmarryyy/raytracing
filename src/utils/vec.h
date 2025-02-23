#pragma once

#include <cstdint>

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
};

struct vec4f {
    float x;
    float y;
    float z;
    float w;
};

vec2f get_normal_form(vec2f v);
vec3f get_normal_form(vec3f v);
vec4f get_normal_form(vec4f v);

void normal(vec2f &v);
void normal(vec3f &v);
void normal(vec4f &v);

float dot(vec3f a, vec3f b);
vec3f cross(vec3f a, vec3f b);

vec3f operator+(vec3f a, vec3f b);
vec3f operator-(vec3f v);
vec3f operator*(vec3f v, float t);
vec3f operator*(float t, vec3f v);
vec3f operator/(vec3f a, vec3f b);

vec4f operator-(vec4f q);

vec3f rotate(vec3f v, vec4f q);
