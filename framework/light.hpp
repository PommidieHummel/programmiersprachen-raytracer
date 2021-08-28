#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include "color.hpp"

struct Light
{
    std::string nameLight;
    glm::vec3 pos;
    Color color;
    float brightness;
};
#endif