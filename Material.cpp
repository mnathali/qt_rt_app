#include "Material.hpp"

using namespace opsll;

Material::Material() : _material_data({{0.5461, 1}})
{
    std::cout << "Default material" << std::endl;

}

Material::Material(std::string_view name)
{
    std::cout << "constructor Material" << std::endl;
}

const std::pair<double, double> &Material::get_n_lambda(double lambda) const
{
    auto it = std::find_if(this->_material_data.begin(), this->_material_data.end(),
        [lambda](auto &spec){return spec.first == lambda;});
    return *it;
}

Material::Material(std::initializer_list<std::pair<double, double>> specs) : _material_data(specs)
{
    std::cout << "initializer list Material" << std::endl;
}

Material::Material(std::vector<std::pair<double, double>> specs) : _material_data(specs) {
        std::cout << "From vector Material" << specs.size() << std::endl;

}

const std::vector<std::pair<double, double>> &Material::get_specs() const {return this->_material_data;}


