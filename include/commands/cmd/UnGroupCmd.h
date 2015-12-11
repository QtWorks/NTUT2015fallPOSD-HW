//
// Created by Raccoon on 2015/12/11.
//

#ifndef POSD_104598003_HW5_UNGROUPCMD_H
#define POSD_104598003_HW5_UNGROUPCMD_H

#include "Command.h"
#include "DrawingWindow.h";

class UnGroupCmd : public Command {

public:
    string checkpoint2;
    bool isExcute = false;
    UnGroupCmd(DrawingWindow *d) : Command(d) { }

public:
    virtual void execute();
    virtual void unexecute();
};


#endif //POSD_104598003_HW5_UNGROUPCMD_H
