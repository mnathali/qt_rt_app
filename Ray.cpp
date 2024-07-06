#include "Ray.hpp"

using namespace opsll;

Ray::Ray(const values_tuple &ray_c, double lambda, double n_lambda) : 
_x(ray_c.x), _y(ray_c.y), _z(ray_c.z), _d(ray_c.d), _cos_x(ray_c.X),
_cos_y(ray_c.Y), _cos_z(ray_c.Z), _lambda(lambda), _n_lambda(n_lambda)
{
    std::cout << "Ray default constructor" << std::endl;
}

// Ray::Ray(const Ray &other) { std::cout << "Ray copy constructor" << std::endl;}
// Ray::~Ray() { std::cout << "Ray destructor" << std::endl;}
// Ray &Ray::operator=(const Ray &other) { std::cout << "Ray operator = " << std::endl; return *this;}

double  Ray::get_wavelenght() const
{
    return this->_lambda;
}

double  Ray::get_n_lambda() const
{
    return this->_n_lambda;
}

std::unique_ptr<opsll::Ray::values_tuple> Ray::get_coordinates() const
{
    auto ptr = std::make_unique<values_tuple>();
    ptr->x = this->_x;
    ptr->y = this->_y;
    ptr->z = this->_z;
    ptr->X = this->_cos_x;
    ptr->Y = this->_cos_y;
    ptr->Z = this->_cos_z;
    ptr->d = this->_d;
    return ptr;
}
