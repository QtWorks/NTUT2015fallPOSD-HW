#include <sstream>
#include "square.h"
#include "boundingbox.h"

Square::Square(int llx, int lly, int length)
	:Shape("square"), _llx(llx), _lly(lly), _length(length) {}

string Square::print() {
	std::ostringstream oss;
	oss << name() << "(" << _llx << "," << _lly << "," << _length << ")";
	return oss.str();
}

int Square::area() const {
	return _length*_length;
}

BoundingBox Square::getBoundingBox() const {
	return BoundingBox(_llx, _lly, _length, _length);
}

string Square::describe(){
	std::ostringstream oss;
	oss << "S" << "(" << _llx << "," << _lly << "," << _length << ")";
	return oss.str();
}