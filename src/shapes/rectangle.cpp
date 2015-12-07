#include <sstream>
#include "rectangle.h"
#include "boundingbox.h"

Rectangle::Rectangle(int x, int y, int w, int h)
	:Shape("rectangle"), _llc(Point(x, y)), _l(h), _w(w) {}

Rectangle::Rectangle(Point p, int w, int h)
	: Shape("rectangle"), _llc(p), _l(h), _w(w) {}

int Rectangle::area() const {
	return _l*_w;
}

string Rectangle::print() {
	std::ostringstream oss;
	oss << name() << "(" << _llc << "," << _w << "," << _l << ")";
	return oss.str();
}

BoundingBox Rectangle::getBoundingBox() const {
	return BoundingBox(_llc.getX(), _llc.getY(), _w, _l);
}
