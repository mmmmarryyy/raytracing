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
        } else if (command == object_commands_names[NEW_PRIMITIVE]) {
            break;
        }
    }

    if (std::find(stages.begin(), stages.end(), false) != stages.end()) {
        throw std::runtime_error("Wrong input file format. Don't have all required fields");
    }

    camera->fov_in_radians.y = 2.0 * std::atan(std::tan(camera->fov_in_radians.x * 0.5) * (float)camera->height / (float)camera->width);

    while (std::getline(in, line)) {
        size_t space_position = line.find(' ');
        if (space_position == std::string::npos) {
            continue;
        }

        std::string command = line.substr(0, space_position);

        if (command == object_commands_names[PLANE]) {
            objects.emplace_back(
                new Plane(
                    get_normal_form(get_vec3f_from_string(line, space_position + 1))
                )
            );
        }
        else if (command == object_commands_names[ELLIPSOID]) {
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
        }

        objects.back()->parse(in);
    }

    std::cout << "DEBUG: End of parse scene; number of objects = " << objects.size() << std::endl;
}

void Scene::render() {
    for (int j = 0; j < camera->height; ++j) {
        for (int i = 0; i < camera->width; ++i) {
            vec2i pixel_position = {i, j};
            Ray ray = camera->cast_in_pixel(pixel_position);

            vec3f color = bg_color;
            double distance = 1e9;

            for (const auto& object : objects) {
                auto intersection = object->is_intersected_by_ray(ray);
                if (intersection.has_value() && intersection.value() < distance) {
                    distance = intersection.value();
                    color = object->color;
                }
            }

            vec3ui new_color = normal_to_rgb(color);

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
    out.write(data_char, image.size() * sizeof(vec3ui));
    out.close();
}
