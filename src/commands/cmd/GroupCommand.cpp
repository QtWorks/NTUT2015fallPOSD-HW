//
// Created by Raccoon on 2016/1/5.
//

#include "ShapeQGraphicsItem.h"
#include "GroupCommand.h"

void GroupCommand::execute() {
    cg = new CompositeGraphics;
    if (executeBackup.empty()) {
        // backup
        for (auto e : items) {
            if (dynamic_cast<ShapeQGraphicsItem *>(e)) {
                executeBackup.push_back(static_cast<ShapeQGraphicsItem *>(e)->getGraphics());
            }
        }
    } else {
        // restore
        model->getModel()->clear();
        for (auto e : executeBackup) {
            model->getModel()->add(e);
        }
    }
    for (auto e : selectedModel) {
        cg->add(e);
        model->getModel()->remove(e);
    }
    model->getModel()->add(cg);
}

void GroupCommand::unexecute() {
    model->getModel()->clear();
    for (auto e : executeBackup) {
        model->getModel()->add(e);
    }
}

GroupCommand::GroupCommand(GraphicsModel *m, QList<QGraphicsItem *> graphicsItems) {
    model = m;
    items = graphicsItems;
    for (auto e : items) {
        if (e->isSelected()) {
            Graphics *item = static_cast<ShapeQGraphicsItem *>(e)->getGraphics();
            selectedModel.push_back(item);
        }
    }
}

GroupCommand::~GroupCommand() {

}
