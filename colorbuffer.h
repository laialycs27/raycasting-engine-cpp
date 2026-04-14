#ifndef COLORBUFFER_H
#define COLORBUFFER_H
#include "types/icolorbuffer.h"
#include "types/line.h"
#include "types/color.h"
#include "types/point.h"
#include "types/serializable.h"
#include "types/point_generator.h"
#include "lib/byte_buffer.h"


namespace types {

class ColorBuffer : public interfaces::IColorBuffer {
public:
    ColorBuffer(uint16_t width, uint16_t height, const Color& background);
    ~ColorBuffer();

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
    uint16_t _width;
    uint16_t _height;
    Color* _pixels;
    Color _background;

    size_t index(uint16_t x, uint16_t y) const;
};

}

#endif
