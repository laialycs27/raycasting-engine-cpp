#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "types/iviewport.h"
#include "types/icolorbuffer.h"
#include "types/point.h"
#include "types/degree.h"
#include "types/raycastresult.h"

namespace types {

class Viewport : public interfaces::IViewport {
public:
    Viewport(interfaces::IColorBuffer* map, interfaces::IColorBuffer* output);

    types::Point location() const override;
    void set_location(const types::Point& location) override;

    types::Degree heading() const override;
    void set_heading(const types::Degree& heading) override;

    size_t ray_count() const override;
    void set_ray_count(const size_t& ray_count) override;

    types::Color ray_color() const override;
    void set_ray_color(const types::Color& ray_color) override;

    types::Degree fov() const;
    void set_fov(const types::Degree& fov);

    const types::RayCastResult* const cast_rays() const override;

    ~Viewport() override;

private:
    types::Point _location;
    types::Degree _heading;
    types::Degree _fov;
    size_t _ray_count;
    types::Color _ray_color;
    interfaces::IColorBuffer* _map;
    interfaces::IColorBuffer* _output;
    size_t _max_distance;

    mutable types::RayCastResult* _ray_results;
};

} 

#endif // VIEWPORT_H
