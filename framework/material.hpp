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
 
std::ostream& print(std::ostream& os)const;
};

std::ostream& operator<<(std::ostream& os,Material const& mat);


#endif