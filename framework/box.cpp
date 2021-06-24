#include "box.hpp"

Box::Box() :
Shape::Shape{"Sphere",{0.0f,0.0f,0.0f}},
min_{0.0f,0.0f,0.0f},
max_{1.0f,1.0f,1.0f}{}


Box::Box(glm::vec3 min,glm::vec3 max) :
Shape::Shape{"Sphere",{0.0f,0.0f,0.0f}},
min_{min},
max_{max}{}


Box::Box(std::string name,std::vector<float> color,glm::vec3 min,glm::vec3 max) :
Shape::Shape{name,color},
min_{min},
max_{max}{}

float Box::area()const{
    auto a = max_.x-min_.x;
    auto b = max_.y-min_.y;
    auto c = max_.z-min_.z;
    return 2*b*c+2*a*b+2*a*c;
    
}

float Box::volum()const{
    auto a = max_.x-min_.x;
    auto b = max_.y-min_.y;
    auto c = max_.z-min_.z;
    return a*b*c;
    
}