
#include "Ray.hpp"
#include "Surface.hpp"
#include "OpticalSystem.hpp"
// #include <boost/geometry.hpp>

int main(int argc, char const *argv[])
{
    // opsll::Ray::values_tuple
    auto coor = opsll::Ray::values_tuple{0,0.01,0,0,0,0,1};
    auto ray = opsll::Ray(coor);
    auto glass = opsll::Material({{0.5461, 1.5}});
    auto s1 = opsll::Surface(0.0, 200.0);
    auto s2 = opsll::Surface(100.0, 0.1, glass);
    auto s3 = opsll::Surface(0.0, 200);
    auto s4 = opsll::Surface(0.0, 0.0);
    for (auto &s: {s1, s2, s3, s4})
    {
        ray = s.convert_ray(ray);
    }
    auto opts = opsll::OpticalSystem();
    
    return 0;
}
