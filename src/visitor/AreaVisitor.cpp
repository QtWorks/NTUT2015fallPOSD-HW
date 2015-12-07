#include "AreaVisitor.h"
#include "compositegraphics.h"
#include "simplegraphics.h"

void AreaVisitor::visitCompositeGraphic(CompositeGraphics *compositeGraphics) {

}

void AreaVisitor::visitSimpleGraphic(SimpleGraphics *simpleGraphics) {
    _areaSum += simpleGraphics->getShape()->area();
}

int AreaVisitor::area() {
    return _areaSum;
}