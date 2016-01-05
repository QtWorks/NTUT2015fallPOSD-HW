//
// Created by Raccoon on 2016/1/6.
//

#include "MoveVisitor.h"
#include "simplegraphics.h"
#include "shape.h"

void MoveVisitor::visitSimpleGraphic(SimpleGraphics *graphics) {
    graphics->getShape()->moveBy(diffX, diffY);
}

void MoveVisitor::visitCompositeGraphic(CompositeGraphics *graphics) {

}

void MoveVisitor::visitRootGraphic(RootGraphics *graphics) {

}

MoveVisitor::MoveVisitor(int diffX, int diffY) {
    this->diffX = diffX;
    this->diffY = diffY;
}
