#ifndef SHAPE_HPP
#define SHAPE_HPP
#define _USE_MATH_DEFINES
#include "material.hpp"
#include "color.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <math.h>
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
    virtual Hitpoint intersect (Ray const& ray)const =0;

    Ray transformRay(glm::mat4 const& mat, Ray const& ray) const;
    void adjustWorldMat();
    void adjustInvWorldMat();
    void scale(float const& x, float const& y, float const& z);
    void translate(float const& x, float const& y, float const& z);
    void rotate(float const& x, float const& y, float const& z, float const& w);


    public:
    std::string name_;
    std::shared_ptr<Material const> material_;
    glm::mat4 world_transformation_;
    glm::mat4 world_transformation_inv_;
    glm::mat4 translateMat_;
    glm::mat4 scaleMat_;
    glm::mat4 rotateMat_;

};

std::ostream& operator<<(std::ostream& os, Shape const& s);
#endif