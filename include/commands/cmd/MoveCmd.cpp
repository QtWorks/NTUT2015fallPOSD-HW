//
// Created by Raccoon on 2015/12/11.
//

#include "MoveCmd.h"
#include "MultiRootGraphicFactory.h"
#include "graphics.h"
#include "DrawingWindow.h"

void MoveCmd::execute() {
    MultiRootGraphicFactory gf;
    Graphics *g = gf.buildGraphicsFromString(this->checkpoint2.c_str());
    if (g) {

        this->w->activateGraphics = g;
        this->w->updateScene();
    }
    return;;
}

void MoveCmd::unexecute() {
    MultiRootGraphicFactory gf;
    Graphics *g = gf.buildGraphicsFromString(this->checkpoint.c_str());
    if (g) {
        this->w->activateGraphics = g;
        this->w->updateScene();
    }
}
