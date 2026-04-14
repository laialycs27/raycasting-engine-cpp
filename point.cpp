#include "types/point.h"
#include <sstream>
#include <iostream>  // Ensure this is included for std::ostream and std::istream

namespace types {

// Adds two points by summing their x and y coordinates
Point Point::operator+(const Point& other) const {
    return Point(_x + other._x, _y + other._y);
}

// Subtracts two points by subtracting their x and y coordinates
Point Point::operator-(const Point& other) const {
    return Point(_x - other._x, _y - other._y);
}

// Reads a Point from an input stream in the format "(x,y)"
std::istream& operator>>(std::istream& stream, Point& p) {
    char ch;
    int x, y;

    stream >> ch; // Expect '('
    if (ch != '(') {
        stream.setstate(std::ios::failbit);
        return stream;
    }

    stream >> x >> ch; // Expect ','
    if (ch != ',') {
        stream.setstate(std::ios::failbit);
        return stream;
    }

    stream >> y >> ch; // Expect ')'
    if (ch != ')') {
        stream.setstate(std::ios::failbit);
        return stream;
    }

    p._x = static_cast<int16_t>(x);
    p._y = static_cast<int16_t>(y);
    return stream;
}

// Writes a Point to an output stream in the format "(x,y)"
std::ostream& operator<<(std::ostream& stream, const Point& p) {
    stream << "(" << p._x << "," << p._y << ")";
    return stream;
}

} 
