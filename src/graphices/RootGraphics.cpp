//
// Created by Raccoon on 2015/12/11.
//

#include "RootGraphics.h"

void RootGraphics::accept(GraphicsVisitor &graphicsVisitor) {
    graphicsVisitor.visitRootGraphic(this);
    for(auto e : this->_graphics){
        e->accept(graphicsVisitor);
    }
}
