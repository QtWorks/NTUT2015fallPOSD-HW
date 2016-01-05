//
// Created by Raccoon on 2016/1/5.
//

#include "DeleteCommand.h"
#include "ShapeQGraphicsItem.h"

void DeleteCommand::execute() {
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
    for (auto e : this->target) {
        this->model->getModel()->remove(e);
    }
}

void DeleteCommand::unexecute() {
    model->getModel()->clear();
    for (auto e : executeBackup) {
        model->getModel()->add(e);
    }
}

DeleteCommand::~DeleteCommand() {

}

DeleteCommand::DeleteCommand(GraphicsModel *m, QList<QGraphicsItem *> model) {
    this->model = m;
    this->items = model;
    for (auto e : this->items) {
        if (e->isSelected()) {
            target.push_back(static_cast<ShapeQGraphicsItem *>(e)->getGraphics());
        }
    }
}
