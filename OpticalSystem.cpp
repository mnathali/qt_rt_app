#include "OpticalSystem.hpp"
#include <cmath>

namespace opsll{

    OpticalSystem::OpticalSystem(double s_1, double field,
            double pup_pos, double pup_size,
            const std::vector<Surface> &surfs,
            const std::vector<double> &waves)
            : _sample_pos_field({s_1, field}), _pupil_pos_diameter({pup_pos, pup_size}),
            _optical_system(surfs), _wave_lines(waves.begin(), waves.end())
    {
        std::cout << "OS created\n";
    }

    std::vector<Surface>::size_type OpticalSystem::size() const {return this->_optical_system.size();}

    void OpticalSystem::add_surface(Surface const &surface)
    {
        this->_optical_system.push_back(surface);
    }

    void OpticalSystem::add_waves(double wave_line)
    {
        this->_wave_lines.insert(wave_line);
    }

    const std::set<double> &OpticalSystem::get_waves() const
    {
        return this->_wave_lines;
    }

    void OpticalSystem::delete_surface(std::vector<Surface>::size_type i)
    {
        if (this->_optical_system.size() > i)
            this->_optical_system.erase(this->_optical_system.begin() + i);
    }

    // boost::geometry::model::point<double, 3,
    //             boost::geometry::cs::cartesian> OpticalSystem::ray_trace(const Ray &&incident_ray)
    // {
    //     Ray ray(incident_ray);
    //     for (auto &s: this->_optical_system)
    //     {
    //         ray = s.convert_ray(ray);
    //     }
    //     return boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian>();
    // }

    const std::vector<Surface> &OpticalSystem::get_surfaces() const {return this->_optical_system;}

    std::vector<Ray> OpticalSystem::ray_trace(Ray ray) const
    {
        std::vector<Ray> rays;
        rays.push_back(ray);
        for (auto &s: this->_optical_system)
        {
            ray = s.convert_ray(ray);
            rays.push_back(ray);
        }
        return rays;
    }

    std::vector<std::vector<Ray>> OpticalSystem::ray_tracing() const
    {
        // std::set<double> fields{0,
        //     0.707 * this->_sample_pos_field.second / 2,
        //     this->_sample_pos_field.second / 2};
        // std::set<std::pair<double, double>> points_on_pupil;
        std::vector<std::vector<Ray>> rays;
        auto ray_coords = this->ray_trace(Ray(opsll::Ray::values_tuple{0,0.1,0,0,0,0,1}));
        rays.push_back(ray_coords);
        return rays;
    }

    double OpticalSystem::get_focal_lengh() const
    {
        auto ray_coords = this->ray_trace(Ray(opsll::Ray::values_tuple{0,0.001,0,0,0,0,1}));
        double last_angle = std::acos(ray_coords.back().get_coordinates()->Z);
        double tang_last = std::tan(last_angle);
        double f = ray_coords.front().get_coordinates()->y / tang_last;
        return f;
    }

    double OpticalSystem::get_pupil_pos(std::vector<Surface> &surfs,
                std::vector<Surface>::size_type n, double wave)
    {
        surfs.resize(n + 1);
        for (auto &s: surfs)
            s = s.get_reversed();
        std::reverse(surfs.begin(), surfs.end());
        OpticalSystem part_os(0, 0, 0, 0, surfs);
        auto ray_traced = part_os.ray_trace(
            Ray(opsll::Ray::values_tuple{0,0,0,0,0, std::sqrt(0.9999), 0.01}));
        ray_traced.pop_back();
        auto last_ray = ray_traced.back();
        auto ray_coords = last_ray.get_coordinates();
        double pup_pos = ray_coords->y ;
    }


}
