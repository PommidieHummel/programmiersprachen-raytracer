#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <iostream>
#include "color.hpp"

struct Material{
    std::string name = " ";
    Color ka = {0,0,0};
    Color kd = {0,0,0};
    Color ks = {0,0,0};
    float m = 0;
};

std::ostream& operator<<(std::ostream& os,Material const& mat){
    os<<"name: "<<mat.name<<"\n"<<"material coefficient: "<<"\n"<<mat.ka<<mat.kd<<mat.ks<<"specular reflection exponent: "<<mat.m<<"\n";
};
#endif