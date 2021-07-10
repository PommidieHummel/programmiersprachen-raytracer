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
    float closest_t = 0.0f;
    auto px1 = min_.x;
    auto t=(px1-r.origin.x)/r.direction.x;
    auto py =(r.origin.y)+t+r.direction.y;
    auto pz =(r.origin.z)+t+r.direction.z;
    if(min_.y<=py&& py<=max_.y&&min_.z<=pz&&pz<=max_.z){
        hit = true;
        closest_t = t;
    }
    auto px2 = max_.x;
    t=(px2-r.origin.x)/r.direction.x;
    py =(r.origin.y)+t+r.direction.y;
    pz =(r.origin.z)+t+r.direction.z;
    if(min_.y<=py&& py<=max_.y&&min_.z<=pz&&pz<=max_.z){
        hit = true;
        if(t<closest_t){
            auto closest_t = t;
        }
    }
    auto py1 = min_.y;
    t=(py1-r.origin.y)/r.direction.y;
    auto px =(r.origin.x)+t+r.direction.x;
    pz =(r.origin.z)+t+r.direction.z;
    if(min_.x<=px&& px<=max_.x&&min_.z<=pz&&pz<=max_.z){
        hit = true;
        if(t<closest_t){
            auto closest_t = t;
        }
    }
    auto py2 = max_.y;
    t=(py2-r.origin.y)/r.direction.y;
    px =(r.origin.x)+t+r.direction.x;
    pz =(r.origin.z)+t+r.direction.z;
    if(min_.x<=px&& px<=max_.x&&min_.z<=pz&&pz<=max_.z){
        hit = true;
        if(t<closest_t){
            auto closest_t = t;
        }
    }
    auto pz1 = min_.z;
    t=(pz1-r.origin.z)/r.direction.z;
    px =(r.origin.x)+t+r.direction.x;
    py =(r.origin.y)+t+r.direction.y;
    if(min_.x<=px&& px<=max_.x&&min_.y<=py&&py<=max_.y){
        hit = true;
        if(t<closest_t){
            auto closest_t = t;
        }
    }
    auto pz2 = max_.z;
    t=(pz2-r.origin.z)/r.direction.z;
    px =(r.origin.x)+t+r.direction.x;
    py =(r.origin.y)+t+r.direction.y;
    if(min_.x<=px&& px<=max_.x&&min_.y<=py&&py<=max_.y){
        hit = true;
        if(t<closest_t){
            auto closest_t = t;
        }
    }
    Hitpoint x{hit,closest_t,name_,material_,r.origin+closest_t*r.direction};
    return x;

}

std::ostream& Box::print(std::ostream& os)const{
    Shape::print(os);
    os<<"min: "<<min_.x<<min_.y<<min_.z<<"\n"<<"max: "<<max_.x<<max_.y<<max_.z<<"\n";

}
