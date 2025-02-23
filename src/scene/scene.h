#pragma once

#include "camera/camera.h"
#include "objects/box.h"
#include "objects/ellipsoid.h"
#include "objects/plane.h"
#include "utils/color.h"
#include "utils/vec.h"
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
    vec3f bg_color;
    std::unique_ptr<Camera> camera{new Camera()};
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<vec3ui> image;

private:
    void initiate_image() {
        if (camera->width <= 0 || camera->height <= 0) {
            throw std::runtime_error("Wrong image size parameters (both should be > 0)");
        }

        image.resize(camera->width * camera->height);
    };

    void set_pixel(vec2i position, vec3ui color) {
        if (
            position.x < 0 || position.x >= camera->width || 
            position.y < 0 || position.y >= camera->height
        ) {
            throw std::runtime_error("Pixel out of image");
        }

        image[camera->width * position.y + position.x] = color;
    };

    vec3ui get_pixel_color(vec2i position) {
        if (
            position.x < 0 || position.x >= camera->width || 
            position.y < 0 || position.y >= camera->height
        ) {
            throw std::runtime_error("Pixel out of image");
        }

        return image[camera->width * position.y + position.x];
    };
};