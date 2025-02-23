#include "vec.h"

vec2f get_normal_form(vec2f vec) {
    float mod = 0.0;
    mod += vec.x * vec.x;
    mod += vec.y * vec.y;

    return {vec.x / mod, vec.y / mod};
}

vec3f get_normal_form(vec3f vec) {
    float mod = 0.0;
    mod += vec.x * vec.x;
    mod += vec.y * vec.y;
    mod += vec.z * vec.z;

    return {vec.x / mod, vec.y / mod, vec.z / mod};
}

vec4f get_normal_form(vec4f vec) {
    float mod = 0.0;
    mod += vec.x * vec.x;
    mod += vec.y * vec.y;
    mod += vec.z * vec.z;
    mod += vec.w * vec.w;

    return {vec.x / mod, vec.y / mod, vec.z / mod, vec.w / mod};
}

void normal(vec2f &vec) {
    float mod = 0.0;
    mod += vec.x * vec.x;
    mod += vec.y * vec.y;

    vec.x /= mod;
    vec.y /= mod;
}

void normal(vec3f &vec) {
    float mod = 0.0;
    mod += vec.x * vec.x;
    mod += vec.y * vec.y;
    mod += vec.z * vec.z;

    vec.x /= mod;
    vec.y /= mod;
    vec.z /= mod;
}

void normal(vec4f &vec) {
    float mod = 0.0;
    mod += vec.x * vec.x;
    mod += vec.y * vec.y;
    mod += vec.z * vec.z;
    mod += vec.w * vec.w;

    vec.x /= mod;
    vec.y /= mod;
    vec.z /= mod;
    vec.w /= mod;
}

vec3f operator+(vec3f vec1, vec3f vec2) {
    return {vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z};
}

vec3f operator-(vec3f vec) {
    return {-vec.x, -vec.y, -vec.z};
}

vec3f operator*(vec3f vec, float t) {
    return {vec.x * t, vec.y * t, vec.z * t};
}

vec3f operator*(float t, vec3f vec) {
    return {vec.x * t, vec.y * t, vec.z * t};
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

vec3f rotate(vec3f vec, vec4f quart) {
    vec3f quart_without_w{quart.x, quart.y, quart.z};

    return 2.0 * dot(quart_without_w, vec) * quart_without_w
        + (quart.w * quart.w - dot(quart_without_w, quart_without_w)) * vec
        + 2.0 * quart.w * cross(quart_without_w, vec);
}
