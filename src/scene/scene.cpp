#include "scene.h"

void Scene::parse() {
    std::cout << "DEBUG: Start of parse scene" << std::endl;
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Can't open file" + filename);
    }

    std::vector<bool> stages(common_commands_names.size(), false);
    std::string line;

    while (std::getline(in, line)) {
        std::string command;
        size_t space_position = line.find(' ');

        if (space_position == std::string::npos) {
            command = line;
        } else {
            command = line.substr(0, space_position);
        }

        if (command == "") {
            continue;
        }
        
        if (command == common_commands_names[DIMENSIONS]) {
            stages[DIMENSIONS] = true;

            glm::ivec2 dimensions = get_vec2i_from_string(line, space_position + 1);
            camera->width = dimensions.x;
            camera->height = dimensions.y;
            initiate_image();
        } else if (command == common_commands_names[BG_COLOR]) {
            stages[BG_COLOR] = true;
            
            bg_color = get_vec3f_from_string(line, space_position + 1);
        } else if (command == common_commands_names[CAMERA_POSITION]) {
            stages[CAMERA_POSITION] = true;

            camera->position = get_vec3f_from_string(line, space_position + 1);
        } else if (command == common_commands_names[CAMERA_RIGHT]) {
            stages[CAMERA_RIGHT] = true;

            camera->right = get_vec3f_from_string(line, space_position + 1);
        } else if (command == common_commands_names[CAMERA_UP]) {
            stages[CAMERA_UP] = true;

            camera->up = get_vec3f_from_string(line, space_position + 1);
        } else if (command == common_commands_names[CAMERA_FORWARD]) {
            stages[CAMERA_FORWARD] = true;

            camera->forward = get_vec3f_from_string(line, space_position + 1);
        } else if (command == common_commands_names[CAMERA_FOV_X]) {
            stages[CAMERA_FOV_X] = true;
            
            float fov_x = get_float_from_string(line, space_position + 1);
            camera->fov_in_radians = {(float)std::tan(fov_x / 2.0), 0};
        } else if (command == common_commands_names[RAY_DEPTH]) {
            stages[RAY_DEPTH] = true;

            ray_depth = get_int_from_string(line, space_position + 1);
        } else if (command == common_commands_names[AMBIENT_LIGHT]) {
            stages[AMBIENT_LIGHT] = true;

            ambient = get_vec3f_from_string(line, space_position + 1);
        } else if (command == common_commands_names[SAMPLES]) {
            stages[SAMPLES] = true;

            samples = get_int_from_string(line, space_position + 1);
        } else if (command == light_commands_names[NEW_LIGHT]) {
            lights.emplace_back(new LightSource());
        } else if (command == object_commands_names[NEW_PRIMITIVE]) {
            if (std::getline(in, line)) {
                space_position = line.find(' ');
                if (space_position == std::string::npos) {
                    continue;
                }

                command = line.substr(0, space_position);

                if (command == object_commands_names[PLANE]) {
                    objects.emplace_back(
                        new Plane(
                            get_vec3f_from_string(line, space_position + 1)
                        )
                    );
                } else if (command == object_commands_names[ELLIPSOID]) {
                    objects.emplace_back(
                        new Ellipsoid(
                            get_vec3f_from_string(line, space_position + 1)
                        )
                    );
                } else if (command == object_commands_names[BOX]) {
                    objects.emplace_back(
                        new Box(
                            get_vec3f_from_string(line, space_position + 1)
                        )
                    );
                } else {
                    std::cout << "DEBUG: Find unknown command inside_flag NEW_PRIMITIVE = " << command << " while parsing input file" << std::endl;
                }
            } else {
                std::cout << "DEBUG: Can't find line after NEW_PRIMITIVE command" << std::endl;
            }
        } else {
            if (!objects.empty()) {
                objects.back()->parse(line);
            } else {
                std::cout << "DEBUG: Find unknown command = " << command << " while parsing input file" << std::endl;
            }
        }
    }

    camera->fov_in_radians.y = camera->fov_in_radians.x * (float)camera->height / (float)camera->width;

    std::cout << "DEBUG: End of parse scene; number of objects = " << objects.size() << std::endl;
}

static std::minstd_rand random_generator = get_random_generator();
std::uniform_real_distribution<float> random_float_distribution;

void Scene::render() {
    // TODO: think about adding parallelism in this function
    for (int j = 0; j < camera->height; ++j) {
        std::cout << "j = " << j << std::endl;
        for (int i = 0; i < camera->width; ++i) {
            glm::vec2 pixel_position = {i, j};
            glm::vec3 pixel_color = {0.0, 0.0, 0.0};
            for (int i = 0; i < samples; i++) {
                Ray ray = camera->cast_in_pixel(
                    pixel_position, 
                    {
                        random_float_distribution(random_generator),
                        random_float_distribution(random_generator)
                    }
                );
                ray.depth = ray_depth;

                pixel_color += get_color(ray);
            }

            pixel_color *= (1.0 / static_cast<float>(samples)); 

            pixel_color = aces_tonemap(pixel_color);
            for (std::size_t i = 0; i < 3; i++) {
                pixel_color[i] = std::pow(pixel_color[i], gamma);
            }
            glm::vec3 new_color = normal_to_rgb(pixel_color);

            set_pixel(pixel_position, new_color);
        }
    }
}

void Scene::draw_to_file(std::string filename) {
    std::ofstream out(filename, std::ios::binary);

    if (!out) {
        throw std::runtime_error("Can't open file" + filename);
    }

    out << "P6" << std::endl << camera->width << " " << camera->height << std::endl << "255" << std::endl;

    char *data_char = (char *)(void *)image.data();
    out.write(data_char, image.size() * 3);
    out.close();
}

std::optional<Intersection> Scene::find_intersection(Ray& ray, float max_distance) {
    Intersection intersection {
        .distance = max_distance,
        .intersected_object_index = -1
    };

    for (int i = 0; i < objects.size(); ++i) {
        std::optional<Intersection> object_intersection = objects[i]->is_intersected_by_ray(ray);
        if (!object_intersection.has_value()) {
            continue;
        }

        if (object_intersection->distance > intersection.distance) {
            continue;
        }

        intersection = object_intersection.value();
        intersection.intersected_object_index = i;
    }

    if (intersection.intersected_object_index < 0) {
        return std::nullopt;
    } else {
        return std::make_optional(intersection);
    }
}

glm::vec3 Scene::get_reflected_color(glm::vec3 &position, glm::vec3 &normal, Ray &ray) {
    Ray reflected_ray(position, ray.direction - 2.0f * normal * glm::dot(normal, ray.direction));
    reflected_ray.depth = ray.depth - 1;
    return get_color(reflected_ray);
}

glm::vec3 Scene::get_color(Ray& ray) {
    if (ray.depth <= 0) {
        return glm::vec3(0.0);
    }

    std::optional<Intersection> intersection = find_intersection(ray);
    if (!intersection.has_value()) {
        return bg_color;
    }

    switch(objects[intersection->intersected_object_index]->material) {
        case Object::Diffuse: {
            glm::vec3 direction = get_random_direction(random_generator, intersection->normal);
            glm::vec3 position = ray.start_position + ray.direction * intersection->distance + shift * intersection->normal;
            
            Ray reflected_ray(position, direction);
            reflected_ray.depth = ray.depth - 1;
            return objects[intersection->intersected_object_index]->emission + get_color(reflected_ray) * objects[intersection->intersected_object_index]->color * 2.0f * glm::dot(direction, intersection->normal);
        }
        case Object::Dielectric: {
            float cos_theta_1 = -glm::dot(intersection->normal, ray.direction);
            float eta_1 = 1.0; // air
            float eta_2 = objects[intersection->intersected_object_index]->ior;

            if (intersection->inside_flag) {
                std::swap(eta_1, eta_2);
            }

            float sin_theta_2 = eta_1 / eta_2 * std::sqrt(1 - cos_theta_1 * cos_theta_1);

            if (sin_theta_2 >= 1.0) {
                glm::vec3 reflected_direction = ray.direction - 2.0f * intersection->normal * glm::dot(
                    intersection->normal, 
                    ray.direction
                );
                glm::vec3 position = ray.start_position + ray.direction * intersection->distance + shift * reflected_direction;
                return get_reflected_color(position, intersection->normal, ray);
            } 
            
            float r0 = std::pow((eta_1 - eta_2) / (eta_1 + eta_2), 2.0);
            float reflection_coefficient = r0 + (1 - r0) * std::pow(1 - cos_theta_1, 5.0);
            float cos_theta_2 = std::sqrt(1 - sin_theta_2 * sin_theta_2);
            glm::vec3 refracted_direction = (eta_1 / eta_2) * ray.direction + 
                    ((eta_1 / eta_2) * cos_theta_1 - cos_theta_2) * intersection->normal;

            if (random_float_distribution(random_generator) < reflection_coefficient) {
                glm::vec3 reflected_direction = ray.direction - 2.0f * intersection->normal * glm::dot(
                    intersection->normal, 
                    ray.direction
                );
                glm::vec3 position = ray.start_position + ray.direction * intersection->distance + shift * reflected_direction;
                return get_reflected_color(position, intersection->normal, ray);
            }
            Ray refracted_ray(ray.start_position + ray.direction * intersection->distance - shift * intersection->normal, refracted_direction);
            refracted_ray.depth = ray.depth - 1;
            glm::vec3 refracted_color = get_color(refracted_ray);

            if (!intersection->inside_flag && refracted_color != bg_color) {
                refracted_color *= objects[intersection->intersected_object_index]->color;
            }
            return refracted_color;
        }
        case Object::Metallic: {
            glm::vec3 position = ray.start_position + ray.direction * intersection->distance + intersection->normal * shift;
            return objects[intersection->intersected_object_index]->emission + 
                objects[intersection->intersected_object_index]->color * 
                get_reflected_color(position, intersection->normal, ray);
        }
    }
}
