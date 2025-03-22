#pragma once

#include "camera/camera.h"
#include "objects/box.h"
#include "objects/ellipsoid.h"
#include "objects/plane.h"
#include "objects/light_source.h"
#include "utils/random.h"
#include "utils/color.h"
#include "utils/common_commands.h"
#include "utils/object_commands.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

class Scene {
public:
    Scene(std::string file): filename(file) {};

    void parse();
    void render();
    void draw_to_file(std::string filename);

    std::string filename;
    glm::vec3 bg_color;
    std::unique_ptr<Camera> camera{new Camera()};
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<LightSource>> lights;
    std::vector<glm::u8vec3> image;
    int ray_depth = 1;
    int samples = 16;
    glm::vec3 ambient = {0.0, 0.0, 0.0};

private:
    const float gamma = 1.0 / 2.2;
    const float shift = 1e-4;

    std::optional<Intersection> find_intersection(Ray& ray, float max_distance = std::numeric_limits<float>::max());
    glm::vec3 get_reflected_color(glm::vec3 &position, glm::vec3 &normal, Ray &ray);
    glm::vec3 get_color(Ray& ray);

    void initiate_image() {
        if (camera->width <= 0 || camera->height <= 0) {
            throw std::runtime_error("Wrong image size parameters (both should be > 0)");
        }

        image.resize(camera->width * camera->height);
    };

    void set_pixel(glm::vec2 position, glm::vec3 color) {
        if (
            position.x < 0 || position.x >= camera->width || 
            position.y < 0 || position.y >= camera->height
        ) {
            throw std::runtime_error("Pixel out of image");
        }

        glm::u8vec3 real_color = color;
        image[camera->width * position.y + position.x] = real_color;
    };

    glm::vec3 get_pixel_color(glm::vec2 position) {
        if (
            position.x < 0 || position.x >= camera->width || 
            position.y < 0 || position.y >= camera->height
        ) {
            throw std::runtime_error("Pixel out of image");
        }

        return image[camera->width * position.y + position.x];
    };
};