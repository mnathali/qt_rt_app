#include "Surface.hpp"

using namespace opsll;

Surface::Surface(double radius, double pos,
                    Material material,
                    movements mov) :
_radius(radius), _pos(pos), _material(material)
{
    std::cout << "Surface constructor" << std::endl;
    this->_curvature = radius == 0 ? 0 : 1 / radius;
}
// Surface::Surface(const Surface &other) { std::cout << "Surface copy constructor" << std::endl;}
// Surface::~Surface() { std::cout << "Surface destructor" << std::endl;}
// Surface &Surface::operator=(const Surface &other) { std::cout << "Surface operator = " << std::endl; return *this;}

double Surface::cross_axis(Ray const &incident_ray) const
{
    auto material_spec = this->get_material().get_n_lambda(incident_ray.get_wavelenght());
    double mu = incident_ray.get_n_lambda() / material_spec.second;
    double curvature = this->get_curvature();
    auto ray_c = incident_ray.get_coordinates();
    double y_ = 1.0;
    while (std::pow(y_, 2) > 0.0001) {
        double l = (ray_c->d - ray_c->z) * ray_c->Z
                    - ray_c->y * ray_c->Y - ray_c->x * ray_c->X;
        double m_z = ray_c->z + l * ray_c->Z - ray_c->d;
        double m_square = std::pow(ray_c->z - ray_c->d, 2) + std::pow(ray_c->y, 2) 
                    + std::pow(ray_c->x, 2) - std::pow(l, 2);
        double cos_eps_square = std::pow(ray_c->Z, 2)
                    - m_square * std::pow(curvature, 2) + 2 * m_z * curvature;
        double cos_eps = std::sqrt(cos_eps_square);
        double L = l + (m_square * curvature - 2 * m_z) / (ray_c->Z + cos_eps);
        
        y_ = ray_c->y + L * ray_c->Y;
    }
    return ray_c->d;
}

Ray Surface::convert_ray(Ray const &incident_ray) const
{
    auto material_spec = this->get_material().get_n_lambda(incident_ray.get_wavelenght());
    double mu = incident_ray.get_n_lambda() / material_spec.second;
    double curvature = this->get_curvature();
    auto ray_c = incident_ray.get_coordinates();
    std::cout << material_spec.first << " | " << material_spec.second << "<-------" << std::endl;
    double l = (ray_c->d - ray_c->z) * ray_c->Z
                - ray_c->y * ray_c->Y - ray_c->x * ray_c->X;
    double m_z = ray_c->z + l * ray_c->Z - ray_c->d;
    double m_square = std::pow(ray_c->z - ray_c->d, 2) + std::pow(ray_c->y, 2) 
                + std::pow(ray_c->x, 2) - std::pow(l, 2);
    double cos_eps_square = std::pow(ray_c->Z, 2)
                - m_square * std::pow(curvature, 2) + 2 * m_z * curvature;
    double cos_eps = std::sqrt(cos_eps_square);
    double L = l + (m_square * curvature - 2 * m_z) / (ray_c->Z + cos_eps);
    
    double x_ = ray_c->x + L * ray_c->X;
    double y_ = ray_c->y + L * ray_c->Y;
    double z_ = ray_c->z + L * ray_c->Z - ray_c->d;
    std::cout << z_ << " = " << ray_c->z << " + " << L << " * " << ray_c->Z << " - " << ray_c->d << std::endl;

    double cos_eps_p_square = 1 - std::pow(mu, 2) * (1 - cos_eps_square);
    double cos_eps_p = std::sqrt(cos_eps_p_square);
    double g = cos_eps_p - mu * cos_eps;

    double Z_ = mu * ray_c->Z + g * (1 - curvature * z_);
    double Y_ = mu * ray_c->Y - g * curvature * y_;
    double X_ = mu * ray_c->X - g * curvature * x_;
    // std::cout << 'x = ' << x_ << " y = " << y_ << " z = " << z_ << std::endl;
    std::cout << " X = " << X_ << " Y = " << Y_ << " Z = " << Z_ << std::endl;
    std::cout << " x = " << x_ << " y = " << y_ << " z = " << z_ << std::endl;
    Ray::values_tuple new_coords{x_, y_, z_, this->get_next_pos(), X_, Y_, Z_};

    auto new_ray = Ray(new_coords, incident_ray.get_wavelenght(), material_spec.second);

    return new_ray;

}

const Material  &Surface::get_material() const
{
    return this->_material;
}

double  Surface::get_curvature() const
{
    return this->_curvature;
}

double  Surface::get_next_pos() const
{
    return this->_pos;
}

double Surface::get_radius() const
{
    return this->_radius;
}

double Surface::get_thick() const
{
    return this->_pos;
}

void Surface::set_radius(double new_radius)
{
    this->_radius = new_radius;
    this->_curvature = new_radius == 0 ? 0 : 1 / new_radius;
}

Surface Surface::get_reversed()
{
    auto new_surfece = Surface(*this);
    new_surfece.set_radius(-this->_radius);
    return new_surfece;
}
