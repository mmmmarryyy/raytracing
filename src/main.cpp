#include <iostream>

#include "scene/scene.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Wrong number of arguments = " << argc - 1 << " (expected: 2)" << std::endl;
        return 1;
    }

    std::string input = argv[1];
    std::string output = argv[2];

    if (output == "") {
        output = "output.ppm";
    }

    Scene scene(input);
    scene.parse();
    
    std::cout << "DEBUG: Start rendering" << std::endl;
    scene.render();

    std::cout << "DEBUG: Start drawing to file" << std::endl;

    scene.draw_to_file(output);

    return 0;
}
