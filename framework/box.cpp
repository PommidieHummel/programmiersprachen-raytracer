#include "box.hpp"

Box::Box() : Shape::Shape{"Sphere", nullptr},
             min_{0.0f, 0.0f, 0.0f},
             max_{1.0f, 1.0f, 1.0f} {}

Box::Box(glm::vec3 min, glm::vec3 max) : Shape::Shape{"Sphere", nullptr},
                                         min_{min},
                                         max_{max} {}

Box::Box(std::string name, std::shared_ptr<Material> const &material, glm::vec3 min, glm::vec3 max) : Shape::Shape{name, material},
                                                                                                      min_{min},
                                                                                                      max_{max} {}

Box::~Box()
{}

float Box::area() const
{
    auto a = max_.x - min_.x;
    auto b = max_.y - min_.y;
    auto c = max_.z - min_.z;
    return 2 * b * c + 2 * a * b + 2 * a * c;
}

float Box::volum() const
{
    auto a = max_.x - min_.x;
    auto b = max_.y - min_.y;
    auto c = max_.z - min_.z;
    return a * b * c;
}
Hitpoint Box::intersect(Ray const &ray) const
{
    Ray r{ transformRay(world_transformation_inv_, ray) };        // nach r umbenannt der faulheit wegen x), übergabeparameter ist nun ray
    bool hit = false;
    glm::vec3 normal;
    float closest_t=10000.0f;
    glm::vec3 hitpoint;
    
    auto t_minDist_x = (min_.x - r.origin.x) / r.direction.x;
    auto t_minDist_y = (min_.y - r.origin.y) / r.direction.y;
    auto t_minDist_z = (min_.z - r.origin.z) / r.direction.z;
    auto t_maxDist_x = (max_.x - r.origin.x) / r.direction.x;
    auto t_maxDist_y = (max_.y - r.origin.y) / r.direction.y;
    auto t_maxDist_z = (max_.z - r.origin.z) / r.direction.z;
    glm::vec3 py_min = r.origin + t_minDist_y * r.direction;
    glm::vec3 py_max = r.origin + t_maxDist_y * r.direction;
    glm::vec3 pz_min = r.origin + t_minDist_z * r.direction;
    glm::vec3 pz_max = r.origin + t_maxDist_z * r.direction;
    glm::vec3 px_min = r.origin + t_minDist_x * r.direction;
    glm::vec3 px_max = r.origin + t_maxDist_x * r.direction;
    



    if (px_min.y <= max_.y && px_min.y >= min_.y && px_min.z <= max_.z && min_.z >= px_min.z)
    {
        hit = true;
        normal={-1,0,0};
        hitpoint =px_min;
        closest_t = t_minDist_x;
    }
    if (px_max.y <= max_.y && min_.y <= px_max.y && px_max.z <= max_.z && min_.z <= px_max.z)
    {
        hit = true;
        normal={1,0,0};
        if (t_maxDist_x < closest_t)
        {
            hitpoint =px_max;
            closest_t = t_maxDist_x;
        }
    }

    if (py_min.x <= max_.x && min_.x<= py_min.x && py_min.z <= max_.z && min_.z <= py_min.z)
    {

        hit = true;
        normal={0,-1,0};
        if (t_minDist_y < closest_t)
        {
            hitpoint =py_min;
            closest_t = t_minDist_y;
        }
    }
    if (py_max.x <= max_.x && min_.x<= py_max.x && py_max.z <= max_.z && min_.z <= py_max.z)
    {
        hit = true;
        normal={0,1,0};
        if (t_maxDist_y < closest_t)
        {
            hitpoint =py_max;
            closest_t = t_maxDist_y;
        }
    }
    if (pz_min.x <= max_.x && min_.x<= pz_min.x && pz_min.y <= max_.y && min_.y <= pz_min.y)
    {
        hit = true;
        normal={0,0,-1};
        if (t_minDist_z < closest_t)
        {
            hitpoint =pz_min;
            closest_t = t_minDist_z;
        }
    }
    if (pz_max.x <= max_.x && min_.x<= pz_max.x && pz_max.y <= max_.y && min_.y <= pz_max.y)
    {

        hit = true;
        normal={0.0f,0.0f,1.0f};
        if (t_maxDist_z < closest_t)
        {
            hitpoint =pz_max;
            closest_t = t_minDist_z;
        }
    }
    glm::mat4 transposeMat = glm::transpose(world_transformation_inv_);      // (winv^-1)^T, für rücktransformation der normalen!
    glm::vec4 v4norm = { normal.x, normal.y, normal.z, 0.f };                     //vec3 zu vec4 für berechnung mit mat4 !
    glm::vec3 normtransposeMat{ transposeMat * v4norm };                          // (winv^-1)^T * v4norm -> vec3 und...
    normal = glm::normalize(normtransposeMat);                                    // ...noch normalisieren
    Hitpoint x{hit, closest_t, name_, material_,hitpoint,normal,r.direction};
    return x;
}

std::ostream &Box::print(std::ostream &os) const
{
    Shape::print(os);
    return os << "min: " << min_.x << min_.y << min_.z << "\n"
       << "max: " << max_.x << max_.y << max_.z << "\n";
}
