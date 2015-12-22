//
// Created by Raccoon on 2015/12/22.
//

#ifndef POSD_104598003_HW5_LOWERLAYERCMD_H
#define POSD_104598003_HW5_LOWERLAYERCMD_H

#include "Command.h"
#include "DrawingWindow.h"

class LowerLayerCmd : public Command {

public:
    string checkpoint2;
    bool isExcute = false;

    LowerLayerCmd(DrawingWindow *d) : Command(d) {
    }

public:
    virtual void execute();
    virtual void unexecute();
};


#endif //POSD_104598003_HW5_LOWERLAYERCMD_H
