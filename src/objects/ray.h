#pragma once

#include "gtc/quaternion.hpp"

class Ray {
public: 
    Ray(glm::dvec3 position, glm::dvec3 d) : start_position(position), direction(d) {}

    Ray shift_and_rotate_ray(glm::dvec3 position, glm::dquat inversed_rotation) {
        Ray ray = Ray(start_position, direction);

        ray.start_position.x -= position.x;
        ray.start_position.y -= position.y;
        ray.start_position.z -= position.z;

        my_rotate(inversed_rotation, ray.start_position);
        my_rotate(inversed_rotation, ray.direction);

        return ray;
    }

    glm::dvec3 start_position;
    glm::dvec3 direction;
    int depth = 0;

private:
    void my_rotate(glm::dquat q, glm::dvec3 &v) {
        glm::dvec3 t = 2.0 * glm::cross({q[1], q[2], q[3]}, v);
        v = v + q[0] * t + cross({q[1], q[2], q[3]}, t);
    }
};
