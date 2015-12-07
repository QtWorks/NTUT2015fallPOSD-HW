#include <string>
#include "graphics.h"
#include "GraphicsVisitor.h"

using std::string;

Graphics::Graphics() {
}

void Graphics::add(Graphics *) {
	throw string("Cannot add child");
}

BoundingBox Graphics::getBoundingBox() const {
	return BoundingBox(0, 0, 0, 0);
}

void Graphics::accept(GraphicsVisitor& graphicsVisitor){

}