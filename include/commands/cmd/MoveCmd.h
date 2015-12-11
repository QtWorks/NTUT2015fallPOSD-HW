//
// Created by Raccoon on 2015/12/11.
//

#ifndef POSD_104598003_HW5_MOVECMD_H
#define POSD_104598003_HW5_MOVECMD_H

#include "Command.h"

class MoveCmd : public Command {

public:
    MoveCmd(DrawingWindow *d) : Command(d) { }
    string checkpoint2;
public:

    virtual void execute();
    virtual void unexecute();
};


#endif //POSD_104598003_HW5_MOVECMD_H
