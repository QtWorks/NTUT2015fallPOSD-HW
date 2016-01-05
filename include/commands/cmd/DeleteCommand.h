//
// Created by Raccoon on 2016/1/5.
//

#ifndef POSD_104598003_HW7_DELETECOMMAND_H
#define POSD_104598003_HW7_DELETECOMMAND_H

#include "Command.h"
#include "simplegraphics.h"
#include "GraphicsModel.h"

#include <QGraphicsItem>

#include <vector>
using std::vector;

class DeleteCommand : public Command {

public:
    DeleteCommand(GraphicsModel *m, QList<QGraphicsItem *> model);

    virtual ~DeleteCommand();

    virtual void execute();

    virtual void unexecute();

private:
    GraphicsModel *model = 0;
    QList<QGraphicsItem *> items;
    vector<Graphics *> executeBackup;
    vector<Graphics *> target;
};


#endif //POSD_104598003_HW7_DELETECOMMAND_H
