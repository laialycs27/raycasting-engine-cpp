#include "viewport.h"
#include "lib/mathutils.h"
#include "types/line.h"
#include "types/point_generator.h"

#include <cmath>
#include <cstdlib>

namespace types
{

    Viewport::Viewport(interfaces::IColorBuffer *map, interfaces::IColorBuffer *output)
        : _location(0, 0),
          _heading(0),
          _fov(60), 
          _ray_count(0),
          _ray_color(Color(255, 255, 255)),
          _map(map),
          _output(output),
          _max_distance(output->diagonal_length()),
          _ray_results(nullptr)
    {
    }

    types::Point Viewport::location() const { return _location; }
    void Viewport::set_location(const types::Point &location) { _location = location; }

    types::Degree Viewport::heading() const { return _heading; }
    void Viewport::set_heading(const types::Degree &heading) { _heading = heading; }

    size_t Viewport::ray_count() const { return _ray_count; }
    void Viewport::set_ray_count(const size_t &ray_count) { _ray_count = ray_count; }

    types::Color Viewport::ray_color() const { return _ray_color; }
    void Viewport::set_ray_color(const types::Color &ray_color) { _ray_color = ray_color; }

    types::Degree Viewport::fov() const { return _fov; }
    void Viewport::set_fov(const types::Degree &fov) { _fov = fov; }

    const types::RayCastResult* const Viewport::cast_rays() const {
        if (_ray_count == 0 || !_map || !_output) {
            return nullptr;
        }

        delete[] _ray_results;
        _ray_results = new types::RayCastResult[_ray_count];

        types::Degree half_fov = _fov / 2.0;
        types::Degree start_angle = _heading - half_fov;
        types::Degree angle_step = _fov / static_cast<int>(_ray_count);

        for (size_t i = 0; i < _ray_count; ++i) {
            types::Degree angle = start_angle + angle_step * static_cast<int>(i + 0.5);

            double dx = mathutils::cos(angle);
            double dy = -mathutils::sin(angle);

            Point target(_location.x() + dx * _max_distance,
                         _location.y() + dy * _max_distance);

            Line ray_line(_location, target, _ray_color);
            interfaces::PointGenerator* gen = ray_line.generator();

            size_t distance = 0;
            Color hit_color = _map->background_color();

            while (gen->has_next() && distance < _max_distance) {
                Point p = gen->next();
                distance++;

                if (p.x() < 0 || p.y() < 0 || p.x() >= _map->width() || p.y() >= _map->height()) {
                    break;
                }

                Color current = _map->get_color_at(p.x(), p.y());

                if (current != _map->background_color()) {
                    hit_color = current;
                    break;
                }

                _output->set_color_at(p.x(), p.y(), _ray_color);
            }

            delete gen;

            _ray_results[i] = RayCastResult(_location, angle, distance, hit_color);
        }

        return _ray_results;
    }

    Viewport::~Viewport()
    {
        delete[] _ray_results;
    }

} 