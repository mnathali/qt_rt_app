#ifndef OPTICALSYSTEM_HPP
#define OPTICALSYSTEM_HPP

#include <vector>
#include <iostream>
#include <set>
#include <limits>
#include "Surface.hpp"
#include "Ray.hpp"
#include <boost/geometry.hpp>
#include <algorithm>

namespace opsll{

    class OpticalSystem
    {
        public:

            OpticalSystem(double s_1 = std::numeric_limits<double>::infinity(),
                double field = 0, double pup_pos = 0, double pup_size = 0,
                const std::vector<Surface> &surfs = std::vector<Surface>(),
                const std::vector<double> &waves = std::vector<double>());
            
            std::vector<Surface>::size_type size() const;

            void add_surface(Surface const &);

            void add_waves(double);
            
            void delete_surface(std::vector<Surface>::size_type i = 0);

            static double get_pupil_pos(std::vector<Surface> &,
                        std::vector<Surface>::size_type n, double wave);

            // boost::geometry::model::point<double, 3,
            //     boost::geometry::cs::cartesian> ray_trace(const Ray &&);

            const std::vector<Surface> &get_surfaces() const;

            std::vector<Ray> ray_trace(Ray incident_ray) const;
            std::vector<std::vector<Ray>> ray_tracing() const;
            double get_focal_lengh() const;

            const std::set<double> &get_waves() const;


        private:

            std::pair<double, double> _sample_pos_field;
            std::pair<double, double> _pupil_pos_diameter;
            std::set<double> _wave_lines;
            std::vector<Surface> _optical_system;
    };


}

#endif // OPTICALSYSTEM_HPP
