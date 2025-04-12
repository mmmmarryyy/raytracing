#include "random.h"

std::minstd_rand get_random_generator() {
    std::random_device rd;
    return std::minstd_rand(rd());
}

double get_random_double(std::minstd_rand& rng, double from, double to) {
    std::uniform_real_distribution<double> random_double_generator(from, to);
    return random_double_generator(rng);
}

uint32_t get_random_uint(std::minstd_rand& rng, uint32_t to) {
    return (rng() % to);
}

glm::dvec3 random_direction_helper(std::minstd_rand& rng) {
    for (;;) {
        glm::dvec3 v = {get_random_double(rng, -1.0, 1.0), get_random_double(rng, -1.0, 1.0), get_random_double(rng, -1.0, 1.0)};
        double norm = glm::dot(v, v);
        if (norm >= 0 && norm <= 1) {
            return v / std::sqrt(norm);
        }
    }
}

glm::dvec3 get_random_direction(std::minstd_rand& rng, glm::dvec3& normal) {
    glm::dvec3 direction = random_direction_helper(rng);
    return direction * (-2.0 * (glm::dot(normal, direction) < 0) + 1.0);
}
