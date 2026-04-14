#include "types/raycastresult.h"
#include <iostream>  

namespace types {

// Writes RayCastResult to output stream in format: (x,y) heading distance rrggbb
std::ostream& operator<<(std::ostream& stream, const RayCastResult& r) {
    stream << r._origin << " "
           << static_cast<int>(r._heading) << " "
           << r._distance << " "
           << r._encountered_color;
    return stream;
}

// Reads RayCastResult from input stream in format: (x,y) heading distance rrggbb
std::istream& operator>>(std::istream& stream, RayCastResult& r) {
    Point origin;
    Degree heading;
    size_t distance;
    Color color;

    stream >> origin >> heading >> distance >> color;

    // Only assign if all reads succeeded
    if (stream) {
        r._origin = origin;
        r._heading = heading;
        r._distance = distance;
        r._encountered_color = color;
    }

    return stream;
}

}
