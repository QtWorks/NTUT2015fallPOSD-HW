#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "boundingbox.h"

class Graphics {
public:
	Graphics();
	virtual BoundingBox getBoundingBox() const;
	virtual void add(Graphics *);
};

#endif // GRAPHICS_H
