
#ifndef RAY_HPP
#define RAY_HPP

#include <iostream>
// #include <boost/geometry.hpp>
#include "Surface.hpp"
#include <memory>

namespace opsll{

    class Surface;

    class Ray
    {
        public:

            struct values_tuple {
                double  x;
                double  y;
                double  z;
                double  d;
                double  X;
                double  Y;
                double  Z;
            };

            Ray(const values_tuple &ray_c = values_tuple{}, double lambda = 0.5461, double n_lambda = 1);
            Ray(const Ray& other) = default;
            Ray(Ray&& other) = default;
            ~Ray() = default;
            Ray &operator=(const Ray& other) = default;
            Ray &operator=(Ray&& other) = default;
            double  get_wavelenght() const;
            double  get_n_lambda() const;
            std::unique_ptr<values_tuple> get_coordinates() const;

        private:

            double _x, _y, _z, _d;
            double _cos_x, _cos_y, _cos_z;
            double _lambda;
            double _n_lambda;
            

    };

}

#endif