#include "vec.h"

float length(vec2f vec) {
    float result = 0.0;

    result += vec.x * vec.x;
    result += vec.y * vec.y;

    return std::sqrt(result);
}

float length(vec3f vec) {
    float result = 0.0;

    result += vec.x * vec.x;
    result += vec.y * vec.y;
    result += vec.z * vec.z;

    return std::sqrt(result);
}

float length(vec4f vec) {
    float result = 0.0;

    result += vec.x * vec.x;
    result += vec.y * vec.y;
    result += vec.z * vec.z;
    result += vec.w * vec.w;

    return std::sqrt(result);
}

vec2f get_normal_form(vec2f vec) {
    float mod = length(vec);
    return {vec.x / mod, vec.y / mod};
}

vec3f get_normal_form(vec3f vec) {
    float mod = length(vec);
    return {vec.x / mod, vec.y / mod, vec.z / mod};
}

vec4f get_normal_form(vec4f vec) {
    float mod = length(vec);
    return {vec.x / mod, vec.y / mod, vec.z / mod, vec.w / mod};
}

void normal(vec2f &vec) {
    float mod = length(vec);
    vec.x /= mod;
    vec.y /= mod;
}

void normal(vec3f &vec) {
    float mod = length(vec);
    vec.x /= mod;
    vec.y /= mod;
    vec.z /= mod;
}

void normal(vec4f &vec) {
    float mod = length(vec);
    vec.x /= mod;
    vec.y /= mod;
    vec.z /= mod;
    vec.w /= mod;
}

vec3f operator+(vec3f vec, float t) {
    return {vec.x + t, vec.y + t, vec.z + t};
}

vec3f operator+(vec3f vec1, vec3f vec2) {
    return {vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z};
}

vec3f &vec3f::operator+=(vec3f other_vec) {
    (*this) = (*this) + other_vec;
    return *this;
}

vec3f operator-(vec3f vec) {
    return {-vec.x, -vec.y, -vec.z};
}

vec3f operator-(vec3f vec1, vec3f vec2) {
    return vec1 + (-vec2);
}

vec3f operator*(vec3f vec, float t) {
    return {vec.x * t, vec.y * t, vec.z * t};
}

vec3f operator*(float t, vec3f vec) {
    return {vec.x * t, vec.y * t, vec.z * t};
}

vec3f operator*(vec3f vec1, vec3f vec2) {
    return {vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z};
}

vec3f &vec3f::operator*=(vec3f other_vec) {
    (*this) = (*this) * other_vec;
    return *this;
}

vec3f &vec3f::operator*=(float t) {
    (*this) = (*this) * t;
    return *this;
}

vec3f operator/(vec3f vec1, vec3f vec2) {
    vec3f result{};
    result.x = vec1.x / vec2.x;
    result.y = vec1.y / vec2.y;
    result.z = vec1.z / vec2.z;
    return result;
}

vec4f operator-(vec4f quart) {
    return {-quart.x, -quart.y, -quart.z, quart.w};
}

float dot(vec3f vec1, vec3f vec2) {
    float s = 0.0;
    s += vec1.x * vec2.x;
    s += vec1.y * vec2.y;
    s += vec1.z * vec2.z;
    return s;
}

vec3f cross(vec3f vec1, vec3f vec2) {
    return {
        vec1.y * vec2.z - vec2.y * vec1.z,
        vec1.z * vec2.x - vec2.z * vec1.x,
        vec1.x * vec2.y - vec2.x * vec1.y
    };
}

vec3f pow(vec3f vec, float power) {
    return {std::pow(vec.x, power), std::pow(vec.y, power), std::pow(vec.z, power)};
}

vec3f rotate(vec3f vec, vec4f quart) {
    vec3f quart_without_w{quart.x, quart.y, quart.z};

    return 2.0 * dot(quart_without_w, vec) * quart_without_w
        + (quart.w * quart.w - dot(quart_without_w, quart_without_w)) * vec
        + 2.0 * quart.w * cross(quart_without_w, vec);
}

vec3f rotate(vec3f vec, vec3f axis, float angle) {
    axis = axis * (std::sin(angle) / 2.0);
    return rotate(vec, {axis.x, axis.y, axis.z, std::cos(angle / 2)});
}

float clamp(float vec, float min, float max) {
    return std::max(std::min(vec, max), min);
}

vec3f clamp(vec3f vec, vec3f min, vec3f max) {
    return {clamp(vec.x, min.x, max.x), clamp(vec.y, min.y, max.y), clamp(vec.z, min.z, max.z)};
}

vec3f aces_tonemap(const vec3f &x) {
    const float a = 2.51;
    const float b = 0.03;
    const float c = 2.43;
    const float d = 0.59;
    const float e = 0.14;

    return clamp(
        (x * (a * x + b)) / 
        (x * (c * x + d) + e), 
        {0.0, 0.0, 0.0}, 
        {1.0, 1.0, 1.0}
    );
}
