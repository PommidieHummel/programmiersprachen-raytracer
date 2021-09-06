#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "material.hpp"
#include "color.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"
#include <iostream>
#include <vector>
#include <memory>


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
    void adjustWorldMat(glm::mat4 const& translMat, glm::mat4 const& rotMat, glm::mat4 const& scaleMat);
    void adjustInvWorldMat();


    public:
    std::string name_;
    std::shared_ptr<Material const> material_;
    glm::mat4 world_transformation_;
    glm::mat4 world_transformation_inv_;

};
std::ostream& operator<<(std::ostream& os, Shape const& s);
#endif