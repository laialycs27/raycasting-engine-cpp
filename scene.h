
#ifndef SCENE_H
#define SCENE_H

#include "types/iscene.h"
#include "colorbuffer.h"
#include "viewport.h"

namespace types {

class Scene : public interfaces::IScene {
public:
    Scene();
    ~Scene() override;

    void init(const std::string name, const uint16_t& width, const uint16_t& height, const Color& background_color = Color::WHITE) override;
    const char* name() const override;
    void set_name(std::string name) override;

    Point viewport_location() const override;
    void set_viewport_location(const Point& location) override;
    Degree viewport_heading() const override;
    void set_viewport_heading(const Degree& heading) override;
    size_t viewport_ray_count() const override;
    void set_viewport_ray_count(const size_t& ray_count) override;
    Color viewport_ray_color() const override;
    void set_viewport_ray_color(const Color& ray_color) override;
    const RayCastResult* const cast_rays() override;

    void render_map(const char* path = nullptr) const override;
    void refresh_output_buffer() override;
    void render_output_buffer(const char* path = nullptr) const override;

    uint16_t width() const override;
    uint16_t height() const override;
    size_t size() const override;
    size_t diagonal_length() const override;
    bool valid() const override;
    Color get_color_at(const uint16_t& x, const uint16_t& y) const override;
    void set_color_at(const uint16_t& x, const uint16_t& y, const Color& color) override;
    Color background_color() const override;
    void set_background_color(const Color& background_color) override;
    void rasterize_line(const Line& line, const size_t& thickness) override;
    void clear() override;
    size_t serialize_to(ByteBuffer& buffer, const size_t& start_index) const override;

private:
    std::string _name;
    bool _initialized;
    interfaces::IColorBuffer* _map;
    interfaces::IColorBuffer* _output;
    interfaces::IViewport* _viewport;

    void check_initialized() const;
};

} 

#endif // SCENE_H
