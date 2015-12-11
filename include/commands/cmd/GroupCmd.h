//
// Created by Raccoon on 2015/12/11.
//

#ifndef POSD_104598003_HW5_GROUPCMD_H
#define POSD_104598003_HW5_GROUPCMD_H

#include "Command.h"
#include "DrawingWindow.h";

class GroupCmd : public Command{

public:
    GroupCmd(DrawingWindow *d) : Command(d) { }
    string checkpoint2;
    bool isExcute = false;

public:
    virtual void execute();
    virtual void unexecute();
};


#endif //POSD_104598003_HW5_GROUPCMD_H
