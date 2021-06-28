#include "shape.hpp"


Shape::Shape():
color_{0.0f,0.0f,0.0f},
name_{"Shape"}{}


Shape::Shape(std::string name,Color color):
name_{name},
color_{color}{}

Shape::~Shape(){
    std::cout<<"Shape deleted \n";
}

std::ostream& Shape::print(std::ostream& os)const{
    os<<"name: "<<name_<<"\n"<<"color: "<<color_;
    return os;
}
std::ostream& operator<<(std::ostream& os, Shape const& s){
    return s.print(os);
}