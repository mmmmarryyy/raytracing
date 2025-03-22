#pragma once

#include "gtc/quaternion.hpp"

class Ray {
public: 
    Ray(glm::vec3 position, glm::vec3 d) : start_position(position), direction(d) {}

    Ray shift_and_rotate_ray(glm::vec3 position, glm::quat inversed_rotation) {
        Ray ray = Ray(start_position, direction);

        ray.start_position.x -= position.x;
        ray.start_position.y -= position.y;
        ray.start_position.z -= position.z;

        my_rotate(inversed_rotation, ray.start_position);
        my_rotate(inversed_rotation, ray.direction);

        return ray;
    }

    glm::vec3 start_position;
    glm::vec3 direction;
    int depth = 0;

private:
    void my_rotate(glm::quat q, glm::vec3 &v) {
        glm::vec3 t = 2.f * glm::cross({q[1], q[2], q[3]}, v);
        v = v + q[0] * t + cross({q[1], q[2], q[3]}, t);
    }
};
