#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <iostream>
#include <vector>

class Shape
{
    public:

    Shape();
    Shape(std::string name, std::vector<float> color);
    virtual float area()const = 0;
    virtual float volum()const = 0;

    protected:
    std::string name_;
    std::vector<float> color_;

};
#endif