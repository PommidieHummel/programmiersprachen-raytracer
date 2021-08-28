#ifndef AMBIENT_HPP
#define AMBIENT_HPP
#include <vector>
#include <glm/vec3.hpp>

struct Ambient{
    std::string ambName{" "};
    glm::vec3 color{0,0,0};
};

#endif