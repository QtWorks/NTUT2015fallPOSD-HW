#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "boundingbox.h"

#include "GraphicsVisitor.h"

class Graphics {
public:
	Graphics();
	virtual BoundingBox getBoundingBox() const;
	virtual void add(Graphics *);
	virtual void remove(Graphics *g);

	virtual void accept(GraphicsVisitor&);


};

#endif // GRAPHICS_H
