//
// Created by Raccoon on 2015/12/22.
//

#include "LowerLayerCmd.h"
#include "MultiRootGraphicFactory.h"

void LowerLayerCmd::execute() {
    if(isExcute){
        MultiRootGraphicFactory gf;
        Graphics *g = gf.buildGraphicsFromString(this->checkpoint2.c_str());
        if (g) {
            this->w->activateGraphics = g;
            this->w->updateScene();
        }
        return;;
    }

    DescriptionVisitor v;
    this->w->activateGraphics->accept(v);
    this->checkpoint = v.getDescription();

    this->w->doLowerLayer();
    isExcute = true;

    DescriptionVisitor v2;
    this->w->activateGraphics->accept(v2);
    this->checkpoint2 = v2.getDescription();
}

void LowerLayerCmd::unexecute() {
    MultiRootGraphicFactory gf;
    Graphics *g = gf.buildGraphicsFromString(this->checkpoint.c_str());
    if (g) {
        this->w->activateGraphics = g;
        this->w->updateScene();
    }
}
