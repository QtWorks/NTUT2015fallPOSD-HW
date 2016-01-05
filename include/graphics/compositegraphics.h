#ifndef COMPOSITEGRAPHICS_H
#define COMPOSITEGRAPHICS_H

#include "graphics.h"

#include <vector>
using std::vector;

class CompositeGraphics : public Graphics {
protected:

public:
	vector<Graphics *> _graphics;
	virtual void add(Graphics *);
	virtual BoundingBox getBoundingBox() const;
	int size() const;
	virtual void accept(GraphicsVisitor& graphicsVisitor);
};

#endif // COMPOSITEGRAPHICS_H
