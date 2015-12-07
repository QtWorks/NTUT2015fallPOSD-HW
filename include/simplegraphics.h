#ifndef SIMPLEGRAPHICS_H
#define SIMPLEGRAPHICS_H

#include "graphics.h"
#include "shape.h"

class SimpleGraphics : public Graphics {
private:
	Shape *_s;
public:
	SimpleGraphics(Shape *s);
	virtual BoundingBox getBoundingBox() const;
};
#endif // SIMPLEGRAPHICS_H
