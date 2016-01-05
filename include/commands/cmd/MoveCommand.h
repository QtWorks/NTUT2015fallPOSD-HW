//
// Created by Raccoon on 2016/1/6.
//

#ifndef POSD_104598003_HW7_MOVECOMMAND_H
#define POSD_104598003_HW7_MOVECOMMAND_H

#include "Command.h"
#include "ShapeQGraphicsItem.h"

class MoveCommand : public Command {

public:
    MoveCommand(ShapeQGraphicsItem *item, int diffX, int diffY);
    virtual void execute();
    virtual void unexecute();
private:
    Graphics *target = 0;
    int diff_x;
    int diff_y;
};


#endif //POSD_104598003_HW7_MOVECOMMAND_H
