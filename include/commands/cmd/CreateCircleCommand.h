//
// Created by Raccoon on 2016/1/5.
//

#ifndef POSD_104598003_HW7_CREATECIRCLECOMMAND_H
#define POSD_104598003_HW7_CREATECIRCLECOMMAND_H

#include "Command.h"
#include "simplegraphics.h"
#include "GraphicsModel.h"

class CreateCircleCommand : public Command {
private:
    SimpleGraphics *circle = 0;
    GraphicsModel *model = 0;
    RootGraphics *root = 0;
public:
    CreateCircleCommand(GraphicsModel *m);
    virtual ~CreateCircleCommand();
    virtual void execute() override;
    virtual void unexecute() override;
};


#endif //POSD_104598003_HW7_CREATECIRCLECOMMAND_H
