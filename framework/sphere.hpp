#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>
 

class Sphere : public Shape {
    public:
    Sphere();
    Sphere(glm::vec3 ctr,float r);
    Sphere(std::string name,Color color,glm::vec3 ctr,float r);
    std::ostream& print(std::ostream& os)const override;
    float area()const override;
    float volum()const override;
    private:
    glm::vec3 ctr_;
    float r_;
};

#endif