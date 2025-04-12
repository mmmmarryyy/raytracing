#pragma once

typedef struct {
    double distance = std::numeric_limits<double>::max();
    glm::dvec3 normal;
    bool inside_flag = false;
    int intersected_object_index = -1;
} Intersection;