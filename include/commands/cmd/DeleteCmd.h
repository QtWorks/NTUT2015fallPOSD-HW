//
// Created by Raccoon on 2015/12/11.
//

#ifndef POSD_104598003_HW5_DELETECMD_H
#define POSD_104598003_HW5_DELETECMD_H

#include "Command.h"
#include "DrawingWindow.h";

class DeleteCmd : public Command{

public:
    string checkpoint2;
    bool isExcute = false;
    DeleteCmd(DrawingWindow *d) : Command(d) { }

public:
    virtual void execute();
    virtual void unexecute();
};


#endif //POSD_104598003_HW5_DELETECMD_H
