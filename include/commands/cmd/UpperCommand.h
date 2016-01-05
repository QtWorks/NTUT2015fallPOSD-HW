//
// Created by Raccoon on 2016/1/5.
//

#ifndef POSD_104598003_HW7_UPPERCOMMAND_H
#define POSD_104598003_HW7_UPPERCOMMAND_H

#include "Command.h"
#include "simplegraphics.h"
#include "compositegraphics.h"
#include "GraphicsModel.h"

#include <QGraphicsScene>

#include <vector>
using std::vector;

class UpperCommand :public Command {
private:
    GraphicsModel *model = 0;
    QList<QGraphicsItem *> items;
    vector<Graphics *> executeBackup;
    vector<Graphics *> contents;
    Graphics *target = 0 ;
    CompositeGraphics *parent = 0;
public:
    UpperCommand(Graphics *target, CompositeGraphics *parent);

    virtual void execute();
    virtual void unexecute();
};


#endif //POSD_104598003_HW7_UPPERCOMMAND_H
