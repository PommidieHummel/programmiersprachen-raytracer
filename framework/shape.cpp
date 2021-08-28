#include "shape.hpp"

Shape::Shape() : material_{nullptr},
                 name_{ "Shape" } {}

Shape::Shape(std::string name, std::shared_ptr<Material> const& material) : name_{name},
                                                                            material_{material} {}

Shape::~Shape()
{
    std::cout << "Shape deleted \n";
}

std::ostream &Shape::print(std::ostream &os) const
{
    os << "name: " << name_ << "\n"
       << "material: "
       << "\n"
       << *material_ << "\n";
    return os;
}


Ray Shape::transformRay(glm::mat4 const& mat, Ray const& ray) const
{
    glm::vec4 ori4{ ray.origin,1 };						//vec3 + 4th Position (1)
    glm::vec4 dir4{ ray.direction,0 };					//vec3 + 4th Position (0)

    glm::vec3 transformedOri{ mat * ori4 };			//now transform back into vec3
    glm::vec3 transformedDir{ mat * dir4 };

    return Ray{ transformedOri,transformedDir };
}

std::ostream &operator<<(std::ostream &os, Shape const &s)
{
    return s.print(os);
}
