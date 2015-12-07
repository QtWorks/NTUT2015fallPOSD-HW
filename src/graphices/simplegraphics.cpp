#include "simplegraphics.h"

SimpleGraphics::SimpleGraphics(Shape *s)
	:_s(s) {}

BoundingBox SimpleGraphics::getBoundingBox() const {
	return _s->getBoundingBox();
}
