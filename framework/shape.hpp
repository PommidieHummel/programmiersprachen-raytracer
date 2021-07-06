#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "color.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <material.hpp>

class Shape
{
    public:
    //Default-Konstruktor
    Shape();
    //Standart-Konstruktor
    Shape(std::string name, std::shared_ptr<Material> const& material);

    ~Shape();

    //virtual methoden, die nur von den abgeleiteten Klassen benutzt werden kann sind =0

    virtual float area()const = 0;
    virtual float volum()const = 0;
    virtual std::ostream& print(std::ostream& os)const;


    protected:
    std::string name_;
    std::shared_ptr<Material const> material_;

};
std::ostream& operator<<(std::ostream& os, Shape const& s);
#endif