#include "box.hpp"

Box::Box() :
Shape::Shape{"Sphere",nullptr},
min_{0.0f,0.0f,0.0f},
max_{1.0f,1.0f,1.0f}{}


Box::Box(glm::vec3 min,glm::vec3 max) :
Shape::Shape{"Sphere",nullptr},
min_{min},
max_{max}{}


Box::Box(std::string name,std::shared_ptr<Material> const& material,glm::vec3 min,glm::vec3 max) :
Shape::Shape{name,material},
min_{min},
max_{max}{}

Box::~Box(){
    std::cout<<"Box deleted \n";
}


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
Hitpoint Box::intersect(Ray const& r)const{
    bool hit = false;
    auto px = min_.x;
    auto t=(px-r.origin.x)/r.direction.x;
    auto py =(r.origin.y)+t+r.direction.y;
    auto pz =(r.origin.z)+t+r.direction.z;
    if(min_.y<=py&& py<=max_.y&&min_.z<=pz&&pz<=max_.z){
        hit = true;
        auto closest_t = t;
    }
}

std::ostream& Box::print(std::ostream& os)const{
    Shape::print(os);
    os<<"min: "<<min_.x<<min_.y<<min_.z<<"\n"<<"max: "<<max_.x<<max_.y<<max_.z<<"\n";

}
