#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <glm/vec3.hpp>

struct Camera
{
    std::string name{" "};
    float fovx{45};
    glm::vec3 eye{0.0f, 0.0f, 0.0f};
    glm::vec3 dir{1.0f, 1.0f, 1.0f};
    glm::vec3 up{0.0f, 0.0f, 1.0f};
};
#endif