#ifndef BOX_HPP
#define BOX_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>

class Box : public Shape {
    public:
    Box();
    Box(glm::vec3 min,glm::vec3 max);
    Box(std::string name, std::vector<float> color,glm::vec3 min,glm::vec3 max);
    float area()const override;
    float volum()const override;
    private:
    glm::vec3 min_;
    glm::vec3 max_;
};
#endif