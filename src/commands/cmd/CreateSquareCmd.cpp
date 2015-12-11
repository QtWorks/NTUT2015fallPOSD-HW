//
// Created by Raccoon on 2015/12/11.
//

#include "CreateSquareCmd.h"
#include "DescriptionVisitor.h"
#include "MultiRootGraphicFactory.h"

void CreateSquareCmd::execute() {
    DescriptionVisitor v;
    this->w->activateGraphics->accept(v);
    this->checkpoint = v.getDescription();

    this->w->doCreateSquare();
}

void CreateSquareCmd::unexecute() {
    MultiRootGraphicFactory gf;
    Graphics *g = gf.buildGraphicsFromString(this->checkpoint.c_str());
    if (g) {
        this->w->activateGraphics = g;
        this->w->updateScene();
    }
}
