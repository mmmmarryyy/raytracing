#include "random.h"

std::minstd_rand get_random_generator() {
    return {std::minstd_rand()};
}

vec3f get_random_direction(std::minstd_rand rng) {
    std::uniform_real_distribution<float> height_distribution(-1.0, 1.0), angle_distribution(0, 2 * M_PI);

    float angle = angle_distribution(rng);
    float height = height_distribution(rng);

    float projection = std::sqrt(1 - height * height);

    return {projection * std::cos(angle), projection * std::sin(angle), height};
}
