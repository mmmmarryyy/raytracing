#include "random.h"

std::minstd_rand get_random_generator() {
    std::random_device rd;
    return std::minstd_rand(rd());
}

glm::vec3 get_random_direction(std::minstd_rand& rng, glm::vec3& normal) {
    std::uniform_real_distribution<float> random_float_generator(-1.0, 1.0);

    for (;;) {
        glm::vec3 v = {random_float_generator(rng), random_float_generator(rng), random_float_generator(rng)};
        float norm = glm::dot(v, v);
        if (norm >= 0 && norm <= 1) {
            if (glm::dot(normal, v) < 0) {
                v = -v;
            }
            return v / static_cast<float>(std::sqrt(norm));
        }
    }
}
