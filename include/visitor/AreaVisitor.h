//
// Created by Raccoon on 2015/10/19.
//

#ifndef AREAVISITOR_H
#define AREAVISITOR_H

#include "GraphicsVisitor.h"

class SimpleGraphics;
class CompositeGraphics;

class AreaVisitor : public GraphicsVisitor {
private:
    int _areaSum = 0;

public:
    virtual void visitSimpleGraphic(SimpleGraphics *simpleGraphics);
    virtual void visitCompositeGraphic(CompositeGraphics *compositeGraphics);
    int area();
};

#endif
