#include <sstream>
#include "point.h"

Point::Point(int x, int y)
        : Shape("point"), _x(x), _y(y) { }

string Point::print() {
    std::ostringstream oss;
    oss << name() << "(" << _x << "," << _y << ")";
    return oss.str();
}

int Point::getX() const {
    return _x;
}

int Point::getY() const {
    return _y;
}

void Point::setX(int _x) {
    this->_x = _x;
}

void Point::setY(int _y) {
    this->_y = _y;
}