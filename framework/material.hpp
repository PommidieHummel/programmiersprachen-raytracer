#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <iostream>
#include "color.hpp"

struct Material{
    std::string name = " ";
    Color ka = {0,0,0};
    Color kd = {0,0,0};
    Color ks = {0,0,0};
    float m = 0.0f;
 
};
/*
std::ostream& operator<<(std::ostream& os,Material const& mat){
    os<<"name: "<<mat.name;
    os<<"material coefficient ka: "<<mat.ka<<"\n";
    os<<"material coefficient kd: "<<mat.kd<<"\n";
    os<<"material coefficient ks: "<<mat.ks<<"\n";
    os<<"specularreflection exponent: "<<mat.m<<"\n";
};*/
#endif