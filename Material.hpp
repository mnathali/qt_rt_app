
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <iostream>
#include <vector>

namespace opsll{

    class Material
    {
        public:

            Material();
            Material(std::string_view name);
            Material(std::initializer_list<std::pair<double, double>> specs);
            Material(std::vector<std::pair<double, double>> specs);
            Material(const Material& other) = default;
            Material(Material&& other) = default;
            ~Material() = default;
            Material &operator=(const Material &other) = default;
            Material &operator=(Material &&other) = default;
            const std::pair<double, double> &get_n_lambda(double lambda) const;
            const std::vector<std::pair<double, double>> &get_specs() const;

        private:

            std::vector<std::pair<double, double>>  _material_data;

    };


}

#endif