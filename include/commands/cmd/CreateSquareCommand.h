//
// Created by Raccoon on 2016/1/5.
//

#ifndef POSD_104598003_HW7_CREATESQUARECOMMAND_H
#define POSD_104598003_HW7_CREATESQUARECOMMAND_H

#include "Command.h"
#include "simplegraphics.h"
#include "GraphicsModel.h"

class CreateSquareCommand : public Command {
private:
    SimpleGraphics *square = 0;
    GraphicsModel *model = 0;
    RootGraphics *root = 0;
public:
    CreateSquareCommand(GraphicsModel *m);
    virtual ~CreateSquareCommand();

    virtual void execute() override;
    virtual void unexecute() override;
};


#endif //POSD_104598003_HW7_CREATESQUARECOMMAND_H
