//
// Created by Raccoon on 2015/12/11.
//

#include "CreateCircleCmd.h"
#include "DescriptionVisitor.h"
#include "MultiRootGraphicFactory.h"

void CreateCircleCmd::execute() {
    DescriptionVisitor v;
    this->w->activateGraphics->accept(v);
    this->checkpoint = v.getDescription();

    this->w->doCreateCircle();
}

void CreateCircleCmd::unexecute() {
    MultiRootGraphicFactory gf;
    Graphics *g = gf.buildGraphicsFromString(this->checkpoint.c_str());
    if (g) {
        this->w->activateGraphics = g;
        this->w->updateScene();
    }
}
