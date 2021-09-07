#include "shape.hpp"

Shape::Shape() : material_{nullptr},
                 name_{ "Shape" } {}
                
Shape::Shape(std::string name, std::shared_ptr<Material> const& material) : name_{name},
                                                                            material_{material} {}

Shape::~Shape()
{}

std::ostream &Shape::print(std::ostream &os) const
{
    os << "name: " << name_ << "\n"
       << "material: "
       << "\n"
       << *material_ << "\n";
    return os;
}


Ray Shape::transformRay(glm::mat4 const& mat, Ray const& ray) const
{
    glm::vec4 ori4{ ray.origin,1.f };						//vec3 + 4th Position (1)
    glm::vec4 dir4{ ray.direction,0.f };					//vec3 + 4th Position (0)

    glm::vec3 transformedOri{ mat * ori4 };			//now transform back into vec3
    glm::vec3 transformedDir{ mat * dir4 };

    return Ray{ transformedOri,transformedDir };
}

void Shape::adjustWorldMat()
{
    world_transformation_ = translateMat_ * rotateMat_ * scaleMat_; //combine all of them to the get final world_transformationMat!
}

void Shape::adjustInvWorldMat()
{
    world_transformation_inv_= glm::inverse(world_transformation_);
}


void Shape::scale(float const& x, float const& y, float const& z)
{
    scaleMat_[0][0] = x;            //mat[col][row]
    scaleMat_[1][1] = y;
    scaleMat_[2][2] = z;
}

void Shape::translate(float const& x, float const& y, float const& z)
{
    translateMat_[3][0] = x;
    translateMat_[3][1] = y;
    translateMat_[3][2] = z;
}

void Shape::rotate(float const& degree, float const& x, float const& y, float const& z)      //x+y+z = means what axis, degree is the angle
{
    //[spalte] [reihe] !!!

    if (x == 1)   //so everything but the x axis line [0] and the last line get the degree stuff
    {
        rotateMat_[1][1] =  cos(degree * M_PI / 180.f);         // cos
        rotateMat_[2][1] = -sin(degree * M_PI / 180.f);         //-sin
        rotateMat_[1][2] =  sin(degree * M_PI / 180.f);         // sin
        rotateMat_[2][2] =  cos(degree * M_PI / 180.f);         // cos
    }
    if (y == 1)   //so everything but the y axis line [1] and the last line get the degree stuff
    {
        rotateMat_[0][0] =  cos(degree * M_PI / 180.f);         // cos
        rotateMat_[2][0] = -sin(degree * M_PI / 180.f);         //-sin
        rotateMat_[0][2] =  sin(degree * M_PI / 180.f);         // sin
        rotateMat_[2][2] =  cos(degree * M_PI / 180.f);         // cos
    }
    if (z == 1)   //so everything but the z axis line [2] and the last line get the degree stuff
    {
        rotateMat_[0][0] =  cos(degree * M_PI / 180.f);         // cos
        rotateMat_[1][0] = -sin(degree * M_PI / 180.f);         //-sin 
        rotateMat_[0][1] =  sin(degree * M_PI / 180.f);         // sin
        rotateMat_[1][1] =  cos(degree * M_PI / 180.f);         // cos
    }
}

std::ostream &operator<<(std::ostream &os, Shape const &s)
{
    return s.print(os);
}
