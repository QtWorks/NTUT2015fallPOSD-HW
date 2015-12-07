#include "compositegraphics.h"
#include "GraphicsVisitor.h"

void CompositeGraphics::add(Graphics *g) {
	_graphics.push_back(g);
}

BoundingBox CompositeGraphics::getBoundingBox() const {
	int llx, lly, urx, ury;

	if (_graphics.size() <= 0) {
		return Graphics::getBoundingBox();
	}

	llx = _graphics[0]->getBoundingBox().llx();
	lly = _graphics[0]->getBoundingBox().lly();
	urx = _graphics[0]->getBoundingBox().urx();
	ury = _graphics[0]->getBoundingBox().ury();

	for (vector<Graphics *>::const_iterator ite = _graphics.begin(); ite != _graphics.end(); ++ite) {
		BoundingBox tmp = (*ite)->getBoundingBox();
		if (tmp.llx() < llx) {
			llx = tmp.llx();
		}
		if (tmp.lly() < lly) {
			lly = tmp.lly();
		}
		if (tmp.urx() > urx) {
			urx = tmp.urx();
		}
		if (tmp.ury() > ury) {
			ury = tmp.ury();
		}
	}
	return BoundingBox(llx, lly, urx - llx, ury - lly);
}

int CompositeGraphics::size() const{
	return _graphics.size();
}

void CompositeGraphics::accept(GraphicsVisitor& graphicsVisitor){
	graphicsVisitor.visitCompositeGraphic(this);
    graphicsVisitor.enter();
	for(auto item : _graphics) {
		item->accept(graphicsVisitor);
	}
    graphicsVisitor.leave();
}