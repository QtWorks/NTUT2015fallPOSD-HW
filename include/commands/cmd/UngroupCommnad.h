//
// Created by Raccoon on 2016/1/5.
//

#ifndef POSD_104598003_HW7_UNGROUPCOMMNAD_H
#define POSD_104598003_HW7_UNGROUPCOMMNAD_H

#include "Command.h"
#include "simplegraphics.h"
#include "GraphicsModel.h"
#include "compositegraphics.h"

#include <QGraphicsScene>

#include <vector>
using std::vector;

class UngroupCommnad :public Command {
private:
    GraphicsModel *model = 0;
    QList<QGraphicsItem *> items;
    CompositeGraphics *target = 0 ;
    vector<Graphics *> executeBackup;
    vector<Graphics *> contents;
public:
    UngroupCommnad(GraphicsModel *m, QList<QGraphicsItem *> model);

    virtual void execute();
    virtual void unexecute();
};


#endif //POSD_104598003_HW7_UNGROUPCOMMNAD_H
