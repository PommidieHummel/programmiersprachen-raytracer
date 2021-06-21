#include "shape.hpp"

Shape::Shape():
color_{0.0f,0.0f,0.0f},
name_{"Shape"}{}

Shape::Shape(std::string name,std::vector<float> color):
name_{name},
color_{color}{}