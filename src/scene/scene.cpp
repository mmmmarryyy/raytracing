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

            vec2i dimensions = get_vec2i_from_string(line, space_position + 1);
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

            camera->right = get_normal_form(get_vec3f_from_string(line, space_position + 1));
        } else if (command == common_commands_names[CAMERA_UP]) {
            stages[CAMERA_UP] = true;

            camera->up = get_normal_form(get_vec3f_from_string(line, space_position + 1));
        } else if (command == common_commands_names[CAMERA_FORWARD]) {
            stages[CAMERA_FORWARD] = true;

            camera->forward = get_normal_form(get_vec3f_from_string(line, space_position + 1));
        } else if (command == common_commands_names[CAMERA_FOV_X]) {
            stages[CAMERA_FOV_X] = true;
            
            float fov_x = get_float_from_string(line, space_position + 1);
            camera->fov_in_radians = {fov_x, 0};
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
                            get_normal_form(get_vec3f_from_string(line, space_position + 1))
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
            if (!objects.empty() && !lights.empty()) {
                objects.back()->parse(line);
                lights.back()->parse(line);
            } else if (!objects.empty()) {
                objects.back()->parse(line);
            } else if (!lights.empty()) {
                lights.back()->parse(line);
            } else {
                std::cout << "DEBUG: Find unknown command = " << command << " while parsing input file" << std::endl;
            }
        }
    }

    camera->fov_in_radians.y = 2.0 * std::atan(std::tan(camera->fov_in_radians.x * 0.5) * (float)camera->height / (float)camera->width);

    std::cout << "DEBUG: End of parse scene; number of objects = " << objects.size() << std::endl;
}

static std::minstd_rand random_generator = get_random_generator();

void Scene::render() {
    // TODO: think about adding parallelism in this function
    std::uniform_real_distribution<float> offset_distribution(-0.5, 0.5);
    std::vector<vec3f> image(camera->height * camera->width, {0.0, 0.0, 0.0});

    for (int s = 0; s < samples; ++s) {
        std::cout << "DEBUG: s = " << s << std::endl;
        for (int j = 0; j < camera->height; ++j) {
            for (int i = 0; i < camera->width; ++i) {
                Ray ray = camera->cast_in_pixel(
                    {
                        i, 
                        j
                    }, 
                    {
                        offset_distribution(random_generator), 
                        offset_distribution(random_generator)
                    }
                );
                ray.depth = ray_depth;

                vec3f sample_color = bg_color;
                std::optional<Intersection> intersection = find_intersection(ray);
                if (intersection.has_value()) {
                    sample_color = intersection->color;
                }

                image[j * camera->width + i] += sample_color;
            }
        }
    }

    for (int j = 0; j < camera->height; ++j) {
        for (int i = 0; i < camera->width; ++i) {
            vec3f color = image[j * camera->width + i] * (1.0 / samples);
            vec3ui new_color = normal_to_rgb(pow(aces_tonemap(color), gamma));

            set_pixel({i, j}, new_color);
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
    out.write(data_char, image.size() * sizeof(vec3ui));
    out.close();
}

std::optional<Intersection> Scene::find_intersection(Ray ray, float max_distance, bool no_light_flag) {
    if (ray.depth <= 0) {
        return std::nullopt;
    }

    ray.depth -= 1;

    Intersection intersection {
        .distance = max_distance,
        .color = {0.0, 0.0, 0.0},
        .inside_flag = false,
    };

    bool intersection_flag = false;
    int intersected_object_index = -1;

    for (int i = 0; i < objects.size(); ++i) {
        std::optional<Intersection> object_intersection = objects[i]->is_intersected_by_ray(ray);
        if (!object_intersection.has_value()) {
            continue;
        }

        if (object_intersection->distance > intersection.distance) {
            continue;
        }

        intersected_object_index = i;
        intersection_flag = true;
        intersection = object_intersection.value();
        intersection.color = objects[i]->emission;
    }

    if (no_light_flag || intersected_object_index < 0) {
        return std::nullopt;
    }

    vec3f position = ray.start_position + ray.direction * intersection.distance;

    switch(objects[intersected_object_index]->material) {
        case Object::Diffuse: {
            vec3f direction = get_random_direction(random_generator);
            if (dot(direction, intersection.normal) < 0) {
                direction = -direction;
            }
            
            Ray reflected_ray(position + direction * shift, direction);
            reflected_ray.depth = ray.depth;
            
            std::optional<Intersection> reflectected_intersection = find_intersection(reflected_ray, max_distance);
            vec3f reflected_color = reflectected_intersection.has_value() ? reflectected_intersection->color : bg_color;
            
            intersection.color += reflected_color * objects[intersected_object_index]->color * 2 * dot(direction, intersection.normal);
            break;
        }
        case Object::Dielectric: {
            float cos_theta_1 = -dot(intersection.normal, ray.direction);
            float eta_1 = 1.0; // air
            float eta_2 = objects[intersected_object_index]->ior;

            if (intersection.inside_flag) {
                std::swap(eta_1, eta_2);
            }

            float sin_theta_2 = eta_1 / eta_2 * std::sqrt(1 - cos_theta_1 * cos_theta_1);

            float reflection_coefficient;
            float direction;

            if (sin_theta_2 >= 1.0) {
                reflection_coefficient = 1.0;
                direction = 0;
            } else {
                float r0 = std::pow((eta_1 - eta_2) / (eta_1 + eta_2), 2.0);
                reflection_coefficient = r0 + (1 - r0) * std::pow(1 - cos_theta_1, 5.0);
                std::uniform_real_distribution<float> ray_direction_distribution(0.0, 1.0);
                direction = ray_direction_distribution(random_generator);
            }

            if (direction < reflection_coefficient) {
                vec3f reflected_direction = get_normal_form(
                    ray.direction - 2 * intersection.normal * dot(
                        intersection.normal, 
                        ray.direction
                    )
                );
                Ray reflected_ray(position + reflected_direction * shift, reflected_direction);
                reflected_ray.depth = ray.depth;

                std::optional<Intersection> reflected_intersection = find_intersection(reflected_ray, max_distance);
                vec3f reflected_color{};
                if (!reflected_intersection.has_value()) {
                    reflected_color = bg_color;
                } else {
                    reflected_color = reflected_intersection->color;
                }
                intersection.color += reflected_color;
            } else {
                float cos_theta_2 = std::sqrt(1 - sin_theta_2 * sin_theta_2);

                vec3f refracted_direction = get_normal_form(
                    (eta_1 / eta_2) * ray.direction + 
                    ((eta_1 / eta_2) * cos_theta_1 - cos_theta_2) * intersection.normal
                );
                Ray refracted_ray(position + refracted_direction * shift, refracted_direction);
                refracted_ray.depth = ray.depth;
                
                std::optional<Intersection> refracted_intersection = find_intersection(refracted_ray, max_distance);

                vec3f refracted_color{};
                if (!refracted_intersection.has_value()) {
                    refracted_color = bg_color;
                } else {
                    refracted_color = refracted_intersection->color;
                    if (!intersection.inside_flag) {
                        refracted_color *= objects[intersected_object_index]->color;
                    }
                }
                intersection.color += refracted_color;
            }
            break;
        }
        case Object::Metallic: {
            vec3f direction = get_normal_form(
                ray.direction - 2 * intersection.normal * dot(
                    intersection.normal, 
                    ray.direction
                )
            );
            Ray reflected_ray(position + direction * shift, direction);
            reflected_ray.depth = ray.depth;

            std::optional<Intersection> reflected_inersection = find_intersection(reflected_ray, max_distance);
            if (!reflected_inersection.has_value()) {
                intersection.color += objects[intersected_object_index]->color * bg_color;
            } else {
                intersection.color += objects[intersected_object_index]->color * reflected_inersection->color;
            }
            break;
        }
    }

        // for (const auto& light : lights) {
        //     vec3f direction;
        //     float light_distance = max_distance;

        //     if (light->light_type == LightSource::Directional) {
        //         direction = light->direction;
        //     } else {
        //         direction = light->position - position;
        //         light_distance = length(direction);
        //         normal(direction);
        //     }

        //     Ray light_ray(position + direction * shift, direction);

        //     std::optional<Intersection> light_intersection = find_intersection(light_ray, light_distance, true);
        //     if (light_intersection.has_value()) {
        //         continue;
        //     }

        //     vec3f light_color = light->intensity;
        //     if (light->light_type == LightSource::Positional) {
        //         light_color *= (1.0 / (light->attenuation.x
        //             + light->attenuation.y * light_distance
        //             + light->attenuation.z * light_distance * light_distance)
        //         );
        //     }

        //     light_color *= std::max(dot(direction, object_intersection->normal), (float)0.0);
        //     intersection.color += object->color * light_color;
        // }

    if (intersection_flag) {
        return std::make_optional(intersection);
    } else {
        return std::nullopt;
    }
}
