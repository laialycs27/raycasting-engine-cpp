#include "scene.h"
#include "colorbuffer.h"
#include "viewport.h"
#include "lib/save_image.h"

#include <stdexcept>
#include <cstring>

namespace types
{

    Scene::Scene() : _initialized(false), _map(nullptr), _output(nullptr), _viewport(nullptr) {}

    void Scene::check_initialized() const
    {
        if (!_initialized)
        {
            throw std::logic_error("Scene not initialized");
        }
    }

    Scene::~Scene()
    {
        delete _map;
        delete _output;
        delete _viewport;
    }

    void Scene::init(const std::string name, const uint16_t &width, const uint16_t &height, const Color &background_color)
    {
        if (name.empty())
            throw std::invalid_argument("Scene name must not be empty");
        if (width == 0 || height == 0)
            throw std::invalid_argument("Scene dimensions must be > 0");

        _name = name;

        delete _map;
        delete _output;
        delete _viewport;

        _map = new ColorBuffer(width, height, background_color);
        _output = new ColorBuffer(width, height, background_color);
        _viewport = new Viewport(_map, _output);

        _viewport->set_location(Point(0, 0));
        _viewport->set_heading(Degree(0));
        _viewport->set_ray_count(0);
        _viewport->set_ray_color(background_color);

        _initialized = true;
    }

    const char *Scene::name() const
    {
        check_initialized();
        return _name.c_str();
    }

    void Scene::set_name(std::string name)
    {
        check_initialized();
        if (name.empty())
            throw std::invalid_argument("Scene name must not be empty");
        _name = name;
    }

    Point Scene::viewport_location() const
    {
        check_initialized();
        return _viewport->location();
    }

    void Scene::set_viewport_location(const Point &location)
    {
        check_initialized();
        if (location.x() < 0 || location.x() >= width() || location.y() < 0 || location.y() >= height())
        {
            throw std::out_of_range("Viewport location out of bounds");
        }
        _viewport->set_location(location);
    }

    Degree Scene::viewport_heading() const
    {
        check_initialized();
        return _viewport->heading();
    }

    void Scene::set_viewport_heading(const Degree &heading)
    {
        check_initialized();
        _viewport->set_heading(heading);
    }

    size_t Scene::viewport_ray_count() const
    {
        check_initialized();
        return _viewport->ray_count();
    }

    void Scene::set_viewport_ray_count(const size_t &ray_count)
    {
        check_initialized();
        size_t capped = ray_count > 360 ? 360 : ray_count;
        _viewport->set_ray_count(capped);
    }

    Color Scene::viewport_ray_color() const
    {
        check_initialized();
        return _viewport->ray_color();
    }

    void Scene::set_viewport_ray_color(const Color &ray_color)
    {
        check_initialized();
        _viewport->set_ray_color(ray_color);
    }

    const RayCastResult *const Scene::cast_rays()
    {
        check_initialized();
        return _viewport->cast_rays();
    }

    void Scene::render_map(const char *path) const
    {
        check_initialized();
        std::string p = path ? path : (_name + "_map.png");

        ByteBuffer bb(_map->size() * 3);
        _map->serialize_to(bb, 0);

        save_image(p, _map->width(), _map->height(), bb);
    }

    void Scene::refresh_output_buffer()
    {
        check_initialized();
        for (uint16_t y = 0; y < height(); ++y)
        {
            for (uint16_t x = 0; x < width(); ++x)
            {
                _output->set_color_at(x, y, _map->get_color_at(x, y));
            }
        }
    }

    void Scene::render_output_buffer(const char *path) const
    {
        check_initialized();
        std::string p = path ? path : (_name + "_output.png");

        ByteBuffer bb(_output->size() * 3);
        _output->serialize_to(bb, 0);

        save_image(p, _output->width(), _output->height(), bb);
    }

    // IColorBuffer overrides

    uint16_t Scene::width() const
    {
        check_initialized();
        return _map->width();
    }

    uint16_t Scene::height() const
    {
        check_initialized();
        return _map->height();
    }

    size_t Scene::size() const
    {
        check_initialized();
        return _map->size();
    }

    size_t Scene::diagonal_length() const
    {
        check_initialized();
        return _map->diagonal_length();
    }

    bool Scene::valid() const
    {
        return _initialized && _map->valid();
    }

    Color Scene::get_color_at(const uint16_t &x, const uint16_t &y) const
    {
        check_initialized();
        return _map->get_color_at(x, y);
    }

    void Scene::set_color_at(const uint16_t &x, const uint16_t &y, const Color &color)
    {
        check_initialized();
        _map->set_color_at(x, y, color);
    }

    Color Scene::background_color() const
    {
        check_initialized();
        return _map->background_color();
    }

    void Scene::set_background_color(const Color &background_color)
    {
        check_initialized();
        _map->set_background_color(background_color);
        _output->set_background_color(background_color);
        _viewport->set_ray_color(background_color);
    }

    void Scene::rasterize_line(const Line &line, const size_t &thickness)
    {
        check_initialized();
        _map->rasterize_line(line, thickness);
    }

    void Scene::clear()
    {
        check_initialized();
        _map->clear();
        _output->clear();
    }

    size_t Scene::serialize_to(ByteBuffer &buffer, const size_t &start_index) const
    {
        check_initialized();
        return _map->serialize_to(buffer, start_index);
    }

}
