
#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <iostream>
#include "Ray.hpp"
#include "Material.hpp"

namespace opsll{

    class Ray;

    class Surface
    {
        public:

            class movements {
                double  _x, _y, _z;
                double  _x_angle, _y_angle, _z_angle;
            };

            Surface(double radius = 0, double pos = 0,
                    Material material = Material(),
                    movements mov = movements{} );
            Surface(const Surface& other) = default;
            Surface(Surface&& other) = default;
            ~Surface() = default;
            Surface &operator=(const Surface &other) = default;
            Surface &operator=(Surface &other) = default;
            Ray convert_ray(Ray const &incident) const;
            const Material  &get_material() const;
            double  get_curvature() const;
            double  get_next_pos() const;

            double get_radius() const;
            double get_thick() const;

            Surface get_reversed();

            double cross_axis(Ray const &incident) const;

        private:

            void set_radius(double);

            double  _radius;
            double  _pos;
            Material    _material;
            double  _x, _y, _z;
            double  _x_angle, _y_angle, _z_angle;
            double  _curvature;

    };

}

#endif