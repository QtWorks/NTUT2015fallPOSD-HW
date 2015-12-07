#ifndef COMPOSITEGRAPHICS_H
#define COMPOSITEGRAPHICS_H

#include <vector>
#include "graphics.h"

using std::vector;

class CompositeGraphics : public Graphics {
private:
	vector<Graphics *> _graphics;
public:
	virtual void add(Graphics *);
	virtual BoundingBox getBoundingBox() const;
};

#endif // COMPOSITEGRAPHICS_H
