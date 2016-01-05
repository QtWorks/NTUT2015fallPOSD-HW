//
// Created by Raccoon on 2016/1/5.
//

#ifndef POSD_104598003_HW7_CREATERECTANGLECOMMAND_H
#define POSD_104598003_HW7_CREATERECTANGLECOMMAND_H

#include "Command.h"
#include "simplegraphics.h"
#include "GraphicsModel.h"

class CreateRectangleCommand: public Command {
private:
    SimpleGraphics *rectangle = 0;
    GraphicsModel *model = 0;
    RootGraphics *root = 0;
public:
    CreateRectangleCommand(GraphicsModel *m);
    virtual ~CreateRectangleCommand();

    virtual void execute() override;
    virtual void unexecute() override;
};


#endif //POSD_104598003_HW7_CREATERECTANGLECOMMAND_H
