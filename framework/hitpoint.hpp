#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include "material.hpp"
#include <glm/vec3.hpp>

struct Hitpoint{
    bool intersect = false;
    float distance = 0;
    std::string objName = " ";
    std::shared_ptr<const Material> const& objMaterial = nullptr;
    glm::vec3 hitpoint = {0.0f,0.0f,0.0f};
    glm::highp_vec3 direction ={1.0f,1.0f,1.0f};


};
#endif