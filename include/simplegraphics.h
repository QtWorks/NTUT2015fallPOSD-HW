#ifndef SIMPLEGRAPHICS_H
#define SIMPLEGRAPHICS_H

#include <string>

#include "graphics.h"
#include "shape.h"

#include "GraphicsVisitor.h"

using std::string;

class SimpleGraphics : public Graphics {
private:
	Shape *_s;
public:
	SimpleGraphics(Shape *s);
	virtual BoundingBox getBoundingBox() const;

	virtual Shape* getShape() const{
		return this->_s;
	}

	virtual void accept(GraphicsVisitor& graphicsVisitor){
		graphicsVisitor.visitSimpleGraphic(this);
	}
};
#endif // SIMPLEGRAPHICS_H
