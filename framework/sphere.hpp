#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>
#include "hitpoint.hpp"
#include "ray.hpp"
 

class Sphere : public Shape {
    public:
    Sphere();
    Sphere(glm::vec3 ctr,float r);
    Sphere(std::string name,std::shared_ptr<Material> const& material,glm::vec3 ctr,float r);
    ~Sphere();
    std::ostream& print(std::ostream& os)const override;
    float area()const override;
    float volum()const override;
    Hitpoint intersect(Ray const& r,float& t)const override;
    private:
    glm::vec3 ctr_;
    float r_;
};

#endif