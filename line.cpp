#include "types/line.h"
#include "lib/mathutils.h" 
#include "types/point_generator.h"

namespace types {

// Constructs a Line using a start point, heading angle, length, and color
types::Line::Line(const Point& start, const Degree& heading, const size_t& length, const Color& color)
    : _start(start), _color(color)
{
    int dx = static_cast<int>(round(length * mathutils::cos(heading)));
    int dy = static_cast<int>(round(length * mathutils::sin(heading)));

    _end = Point(_start.x() + dx, _start.y() + dy);
}

// External generator factory (likely defined in point_generator.cpp)
extern interfaces::PointGenerator* create_generator(const types::Point&, const types::Point&);

interfaces::PointGenerator* const Line::generator() const {
    return create_generator(_start, _end);
}

// Writes Line to an output stream in format: (x1,y1) (x2,y2) rrggbb
std::ostream& operator<<(std::ostream& stream, const Line& l) {
    stream << l._start << " " << l._end << " " << l._color;
    return stream;
}

// Reads Line from an input stream in format: (x1,y1) (x2,y2) rrggbb
std::istream& operator>>(std::istream& stream, Line& l) {
    Point start, end;
    Color color;

    stream >> start >> end >> color;

    if (stream) {
        l._start = start;
        l._end = end;
        l._color = color;
    }

    return stream;
}

} 
