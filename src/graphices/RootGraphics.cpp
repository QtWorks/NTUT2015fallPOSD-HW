//
// Created by Raccoon on 2015/12/11.
//

#include "RootGraphics.h"

void RootGraphics::accept(GraphicsVisitor &graphicsVisitor) {
    graphicsVisitor.visitRootGraphic(this);
    for (auto e : this->_graphics) {
        e->accept(graphicsVisitor);
    }
}

void RootGraphics::remove(Graphics *g) {
    for (vector<Graphics *>::iterator it = _graphics.begin(); it != _graphics.end(); it++) {
        if ((*it) == g) {
            _graphics.erase(it);
            break;
        }
    }
}

void RootGraphics::clear() {
    _graphics.clear();
}
