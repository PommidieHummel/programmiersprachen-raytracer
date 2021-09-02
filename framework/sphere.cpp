#define _USE_MATH_DEFINES
#include "sphere.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

Sphere::Sphere() :
Shape::Shape{"Sphere",nullptr},
ctr_{0.0f,0.0f,0.0f},
r_{1.0f}{}


Sphere::Sphere(glm::vec3 ctr,float r) :
Shape::Shape{"Sphere",nullptr},
ctr_{ctr},
r_{r}{}


Sphere::Sphere(std::string name,std::shared_ptr<Material> const& material,glm::vec3 ctr,float r) :
Shape::Shape{name,material},
ctr_{ctr},
r_{r}{}

Sphere::~Sphere(){
    std::cout<< name_ <<" deleted \n";
}

float Sphere::area()const{
    return 4* M_PI*r_*r_;
}

float Sphere::volum()const{
    return (4* M_PI*r_*r_*r_)/3;
}

Hitpoint Sphere::intersect(Ray const& r)const{
    float distance = 1.0f;
    Ray tranfsRay{transformRay(world_transformation_inv_, r)};            //use inverse transfmatrix on the ray
    bool hit = glm::intersectRaySphere(r.origin,glm::normalize(r.direction),ctr_,pow(r_,2),distance);
    Hitpoint x {hit,distance,name_,material_,r.origin+ distance*r.direction, r.direction};
    return x;

}

std::ostream& Sphere::print(std::ostream& os)const{
    Shape::print(os);
    return os<<"centre: "<<ctr_.x<<ctr_.y<<ctr_.z<<"\n"<<"radius: "<<r_<<"\n";
    

}
