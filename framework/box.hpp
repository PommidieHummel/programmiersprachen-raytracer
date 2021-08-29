#ifndef BOX_HPP
#define BOX_HPP
#include "shape.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"
#include <glm/vec3.hpp>

class Box : public Shape
{
public:
    Box();
    Box(glm::vec3 min, glm::vec3 max);
    Box(std::string name, std::shared_ptr<Material> const &material, glm::vec3 min, glm::vec3 max);
    ~Box();
    float area() const override;
    float volum() const override;
    std::ostream &print(std::ostream &os) const override;
    Hitpoint intersect(Ray const &r) const override;

private:
    glm::vec3 min_;
    glm::vec3 max_;
};
#endif