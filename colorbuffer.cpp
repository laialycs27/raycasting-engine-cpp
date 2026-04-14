#include "colorbuffer.h"
#include "lib/byte_buffer.h"
#include <cmath> 

namespace types {

ColorBuffer::ColorBuffer(uint16_t width, uint16_t height, const Color& background)
    : _width(width), _height(height), _background(background) {
    _pixels = new Color[static_cast<size_t>(_width) * _height];
    clear();
}

ColorBuffer::~ColorBuffer() {
    delete[] _pixels;
}

uint16_t ColorBuffer::width() const {
    return _width;
}

uint16_t ColorBuffer::height() const {
    return _height;
}

size_t ColorBuffer::size() const {
    return static_cast<size_t>(_width) * _height;
}

size_t ColorBuffer::diagonal_length() const {
    return static_cast<size_t>(std::sqrt(_width * _width + _height * _height));
}

bool ColorBuffer::valid() const {
    return _pixels != nullptr && _width > 0 && _height > 0;
}

Color ColorBuffer::get_color_at(const uint16_t& x, const uint16_t& y) const {
    if (x >= _width || y >= _height) {
        throw std::out_of_range("get_color_at: coordinates out of bounds");
    }
    return _pixels[index(x, y)];
}

void ColorBuffer::set_color_at(const uint16_t& x, const uint16_t& y, const Color& color) {
    if (x >= _width || y >= _height) {
        return; // ignore out-of-bounds
    }
    _pixels[index(x, y)] = color;
}

Color ColorBuffer::background_color() const {
    return _background;
}

void ColorBuffer::set_background_color(const Color& new_background) {
    for (size_t i = 0; i < size(); ++i) {
        if (_pixels[i] == _background) {
            _pixels[i] = new_background;
        }
    }
    _background = new_background;
}

void ColorBuffer::rasterize_line(const Line& line, const size_t& thickness) {
    interfaces::PointGenerator* gen = line.generator();

    size_t thick = thickness > 0 ? thickness : 1;
    int radius = static_cast<int>(thick / 2);

    while (gen->has_next()) {
        Point p = gen->next();
        int px = p.x();
        int py = p.y();

        for (int dx = -radius; dx <= radius; ++dx) {
            for (int dy = -radius; dy <= radius; ++dy) {
                int nx = px + dx;
                int ny = py + dy;

                if (nx >= 0 && ny >= 0 && nx < _width && ny < _height) {
                    set_color_at(nx, ny, line.color());
                }
            }
        }
    }

    delete gen;
}

void ColorBuffer::clear() {
    for (size_t i = 0; i < size(); ++i) {
        _pixels[i] = _background;
    }
}

size_t ColorBuffer::serialize_to(ByteBuffer& buffer, const size_t& start_index) const {
    size_t count = 0;
    if (start_index + 3 * size() > buffer.capacity()) {
        return 0;
    }

    for (size_t i = 0; i < size(); ++i) {
        count += _pixels[i].serialize_to(buffer, start_index + count);
    }

    return count;
}

size_t ColorBuffer::index(uint16_t x, uint16_t y) const {
    return static_cast<size_t>(y) * _width + x;
}

} 
