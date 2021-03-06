#include "rectangle.h"
#include "boundingbox.h"

#include <string>
#include <sstream>
using std::string;

Rectangle::Rectangle(int x, int y, int w, int h)
        : Shape("rectangle"), _llc(Point(x, y)), _l(h), _w(w) { }

Rectangle::Rectangle(Point p, int w, int h)
        : Shape("rectangle"), _llc(p), _l(h), _w(w) { }

int Rectangle::area() const {
    return _l * _w;
}

string Rectangle::print() {
    std::ostringstream oss;
    oss << this->name() << "(" << _llc << "," << _w << "," << _l << ")";
    return oss.str();
}

BoundingBox Rectangle::getBoundingBox() const {
    return BoundingBox(_llc.getX(), _llc.getY(), _w, _l);
}

string Rectangle::describe() {
    std::ostringstream oss;
    oss << "R" << "(" << _llc.getX() << "," << _llc.getY() << "," << _w << "," << _l << ")";
    return oss.str();
};

int Rectangle::getX() const {
    return _llc.getX();
}

int Rectangle::getY() const {
    return _llc.getY();
}

int Rectangle::getWidth() {
    return _w;
}

int Rectangle::getHeight() {
    return _l;
}

void Rectangle::moveBy(int x, int y) {
    this->_llc.setX(_llc.getX() + x);
    this->_llc.setY(_llc.getY() + y);
}
