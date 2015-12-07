#include "rectangle.h"
#include "boundingbox.h"

BoundingBox::BoundingBox(int x, int y, int w, int h)
	:Rectangle(x,y,w,h), _llx(x), _lly(y), _l(h), _w(w) {}

int BoundingBox::llx() const {
	return _llx;
}

int BoundingBox::lly() const {
	return _lly;
}

int BoundingBox::urx() const {
	return _llx + _w;
}

int BoundingBox::ury() const {
	return _lly + _l;
}
