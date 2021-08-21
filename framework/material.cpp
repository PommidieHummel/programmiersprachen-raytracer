#include "material.hpp"

std::ostream &Material::print(std::ostream &os) const
{
    os << "material name: " << name << "\n"
       << "material coefficient ka: " << ka << "\n"
       << "material coefficient kd: " << kd << "\n"
       << "material coefficient ks: " << ks << "\n"
       << "specularreflection exponent: " << m << "\n";
    return os;
}
std::ostream &operator<<(std::ostream &os, Material const &mat)
{
    return mat.print(os);
};