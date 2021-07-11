#include "shape.hpp"

Shape::Shape():
material_{nullptr},
name_{"Shape"}{}


Shape::Shape(std::string name,std::shared_ptr<Material> const& material):
name_{name},
material_{material}{}

Shape::~Shape(){
    std::cout<<"Shape deleted \n";
}

std::ostream& Shape::print(std::ostream& os)const{
    os<<"name: "<<name_;
    return os;
}
std::ostream& operator<<(std::ostream& os, Shape const& s){
    return s.print(os);
}