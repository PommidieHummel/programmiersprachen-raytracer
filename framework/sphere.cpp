#include "sphere.hpp"
#include <cmath>

Sphere::Sphere() :
Shape::Shape{"Sphere",{0.0f,0.0f,0.0f}},
ctr_{0.0f,0.0f,0.0f},
r_{0.0f}{}


Sphere::Sphere(glm::vec3 ctr,float r) :
Shape::Shape{"Sphere",{0.0f,0.0f,0.0f}},
ctr_{ctr},
r_{r}{}


Sphere::Sphere(std::string name,std::vector<float> color,glm::vec3 ctr,float r) :
Shape::Shape{name,color},
ctr_{ctr},
r_{r}{}

float Sphere::area()const{
    return 4* M_PI*r_*r_;
}

float Sphere::volum()const{
    return (4/3)* M_PI*r_*r_*r_;
}


