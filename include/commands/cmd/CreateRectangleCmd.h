//
// Created by Raccoon on 2015/12/11.
//

#ifndef POSD_104598003_HW5_CREATERECTANGLECMD_H
#define POSD_104598003_HW5_CREATERECTANGLECMD_H

#include "Command.h"
#include "DrawingWindow.h";

class CreateRectangleCmd : public Command{

public:
    CreateRectangleCmd(DrawingWindow *d) : Command(d) { }

public:
    virtual void execute();
    virtual void unexecute();
};


#endif //POSD_104598003_HW5_CREATERECTANGLECMD_H
