#include <iostream>
#include <vector>

class Shape
{
    public:

    Shape();
    Shape(std::string name, std::vector<float> color);
    virtual float area()const;
    virtual float volum()const;

    private:
    std::string name_;
    std::vector<float> color_;

};