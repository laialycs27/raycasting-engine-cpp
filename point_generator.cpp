#include "types/point.h"
#include "types/point_generator.h"

namespace {

class BresenhamGenerator : public interfaces::PointGenerator {
private:
    types::Point _start;
    types::Point _end;
    types::Point _current;

    int dx, dy, sx, sy, err;
    bool _has_next;

public:
    BresenhamGenerator(const types::Point& start, const types::Point& end)
        : _start(start), _end(end), _current(start), _has_next(true) {
        int x1 = _start.x(), y1 = _start.y();
        int x2 = _end.x(), y2 = _end.y();

        dx = abs(x2 - x1);
        dy = abs(y2 - y1);
        sx = (x1 < x2) ? 1 : -1;
        sy = (y1 < y2) ? 1 : -1;
        err = dx - dy;
    }

    types::Point start() const override {
        return _start;
    }

    types::Point end() const override {
        return _end;
    }

    bool has_next() const override {
        return _has_next;
    }

    types::Point next() override {
        if (!_has_next) {
            return _end;
        }

        types::Point result = _current;

        if (_current == _end) {
            _has_next = false;
            return result;
        }

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            _current = types::Point(_current.x() + sx, _current.y());
        }

        if (e2 < dx) {
            err += dx;
            _current = types::Point(_current.x(), _current.y() + sy);
        }

        return result;
    }
};

} 

//  Moved create_generator into `types` namespace to match linker expectations
namespace types {
interfaces::PointGenerator* create_generator(const types::Point& start, const types::Point& end) {
    return new BresenhamGenerator(start, end);
}
}
