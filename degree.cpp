#include "types/degree.h"

namespace types {

// Normalize any integer value to be within [0, 360)
static int normalize(int v) {
    v %= Degree::DEGREE_SUP;
    if (v < 0) v += Degree::DEGREE_SUP;
    return v;
}

// Constructor from int
Degree::Degree(const int& value) {
    this->value = normalize(value);
}

// Assignment from int
Degree& Degree::operator=(const int& v) {
    value = normalize(v);
    return *this;
}

// Arithmetic: Degree + Degree
Degree Degree::operator+(const Degree& other) const {
    return Degree(value + other.value);
}

// Arithmetic: Degree - Degree
Degree Degree::operator-(const Degree& other) const {
    return Degree(value - other.value);
}

// Arithmetic: Degree + int
Degree Degree::operator+(const int& rhs) const {
    return Degree(value + rhs);
}

// Arithmetic: Degree - int
Degree Degree::operator-(const int& rhs) const {
    return Degree(value - rhs);
}

// Compound assignment: +=
Degree& Degree::operator+=(const Degree& other) {
    value = normalize(value + other.value);
    return *this;
}

// Compound assignment: -=
Degree& Degree::operator-=(const Degree& other) {
    value = normalize(value - other.value);
    return *this;
}

// Pre-increment (++d)
Degree& Degree::operator++() {
    value = normalize(value + 1);
    return *this;
}

// Post-increment (d++)
Degree Degree::operator++(int) {
    Degree old = *this;
    value = normalize(value + 1);
    return old;
}

// Pre-decrement (--d)
Degree& Degree::operator--() {
    value = normalize(value - 1);
    return *this;
}

// Post-decrement (d--)
Degree Degree::operator--(int) {
    Degree old = *this;
    value = normalize(value - 1);
    return old;
}

// Type conversion to int
Degree::operator int() const {
    return value;
}

// Output stream <<
std::ostream& operator<<(std::ostream& stream, const Degree& d) {
    return stream << d.value;
}

// Input stream >>
std::istream& operator>>(std::istream& stream, Degree& d) {
    int temp;
    stream >> temp;
    d.value = normalize(temp);
    return stream;
}

} 
