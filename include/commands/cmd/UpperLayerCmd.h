//
// Created by Raccoon on 2015/12/22.
//

#ifndef POSD_104598003_HW5_UPPERLAYERCMD_H
#define POSD_104598003_HW5_UPPERLAYERCMD_H

#include "Command.h"
#include "DrawingWindow.h"

class UpperLayerCmd : public Command {

public:
    string checkpoint2;
    bool isExcute = false;

    UpperLayerCmd(DrawingWindow *d) : Command(d) { }
    virtual void execute();
    virtual void unexecute();
};


#endif //POSD_104598003_HW5_UPPERLAYERCMD_H
