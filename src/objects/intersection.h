#pragma once

typedef struct {
    float distance = std::numeric_limits<float>::max();
    glm::vec3 normal;
    bool inside_flag = false;
    int intersected_object_index = -1;
} Intersection;