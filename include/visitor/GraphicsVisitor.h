//
// Created by Raccoon on 2015/10/6.
//

#ifndef GRAPHICSVISITOR_H
#define GRAPHICSVISITOR_H

class SimpleGraphics;
class CompositeGraphics;

class GraphicsVisitor {
public:
    virtual void visitSimpleGraphic(SimpleGraphics*) = 0;
    virtual void visitCompositeGraphic(CompositeGraphics*) = 0;
    virtual void enter(){}
    virtual void leave(){}
};



#endif
