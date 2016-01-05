#include "circle.h"
#include "boundingbox.h"

#include <sstream>

Circle::Circle(int cx, int cy, int radius)
        : Shape("circle"), _cx(cx), _cy(cy), _radius(radius) { }

string Circle::print() {
    std::ostringstream oss;
    oss << name() << "(" << _cx << "," << _cy << "," << _radius << ")";
    return oss.str();
}

BoundingBox Circle::getBoundingBox() const {
    BoundingBox box(_cx - _radius, _cy - _radius, _radius * 2, _radius * 2);
    return box;
}

int Circle::area() const {
    return 3 * _radius * _radius;
}

string Circle::describe() {
    std::ostringstream oss;
    oss << "C" << "(" << _cx << "," << _cy << "," << _radius << ")";
    return oss.str();
}

int Circle::getX() const {
    return _cx;
}

int Circle::getY() const {
    return _cy;
}

int Circle::getRadius() const {
    return _radius;
}

void Circle::moveBy(int x, int y) {
    this->_cx += x;
    this->_cy += y;
}
