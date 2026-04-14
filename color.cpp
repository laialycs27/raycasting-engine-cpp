#include "types/color.h"
#include "lib/byte_buffer.h"
#include <iomanip>
#include <sstream>

namespace types {

Color::Color(const uint32_t& base) {
    _r = (base >> 16) & 0xFF;
    _g = (base >> 8) & 0xFF;
    _b = base & 0xFF;
}

Color::Color(const ByteBuffer& buffer, const size_t start_index) {
    if (start_index + 2 >= buffer.capacity()) {
        _r = _g = _b = 255;
        return;
    }
    _r = buffer[start_index];
    _g = buffer[start_index + 1];
    _b = buffer[start_index + 2];
}

Color& Color::operator=(const uint32_t& base) {
    _r = (base >> 16) & 0xFF;
    _g = (base >> 8) & 0xFF;
    _b = base & 0xFF;
    return *this;
}

Color::operator uint32_t() const {
    return (_r << 16) | (_g << 8) | _b;
}

size_t Color::serialize_to(ByteBuffer& buffer, const size_t& start_index) const {
    if (start_index + 2 >= buffer.capacity()) {
        return 0;
    }
    buffer[start_index] = _r;
    buffer[start_index + 1] = _g;
    buffer[start_index + 2] = _b;
    return 3;
}

std::ostream& operator<<(std::ostream& stream, const Color& color) {
    stream << std::hex << std::setfill('0')
           << std::setw(2) << static_cast<int>(color._r)
           << std::setw(2) << static_cast<int>(color._g)
           << std::setw(2) << static_cast<int>(color._b)
           << std::dec;
    return stream;
}

std::istream& operator>>(std::istream& stream, Color& color) {
    std::string hex;
    stream >> hex;

    if (hex.length() != 6) {
        color = Color();
        return stream;
    }

    unsigned int r, g, b;
    std::stringstream ss;

    ss << std::hex << hex.substr(0, 2);
    ss >> r;
    ss.clear(); ss.str(hex.substr(2, 2));
    ss >> g;
    ss.clear(); ss.str(hex.substr(4, 2));
    ss >> b;

    color = Color(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b));
    return stream;
}

} 
