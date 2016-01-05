//
// Created by Raccoon on 2016/1/5.
//

#ifndef POSD_104598003_HW7_GROUPCOMMAND_H
#define POSD_104598003_HW7_GROUPCOMMAND_H

#include "Command.h"
#include "simplegraphics.h"
#include "GraphicsModel.h"

#include <QGraphicsScene>

#include <vector>
using std::vector;

class GroupCommand : public Command {
private:
    GraphicsModel *model = 0;
    QList<QGraphicsItem *> items;
    QList<QGraphicsItem *> selectedItems;
    CompositeGraphics *cg = 0;

    vector<Graphics *> executeBackup;

    vector<Graphics *> selectedModel;

public:
    GroupCommand(GraphicsModel *m, QList<QGraphicsItem *> model);

    virtual ~GroupCommand();

    virtual void execute();

    virtual void unexecute();
};


#endif //POSD_104598003_HW7_GROUPCOMMAND_H
