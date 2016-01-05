//
// Created by Raccoon on 2016/1/5.
//

#include "UngroupCommnad.h"
#include "compositegraphics.h"
#include "CompositeQGraphicsItem.h"
#include <QGraphicsItem>

UngroupCommnad::UngroupCommnad(GraphicsModel *m, QList<QGraphicsItem *> model) {
    this->model = m;
    this->items = model;
    for (auto e : model) {
        if (e->isSelected()) {
            target = static_cast<CompositeGraphics *>(static_cast<CompositeQGraphicsItem *>(e)->getGraphics());
            for (auto i : target->_graphics) {
                this->contents.push_back(i);
            }
            break;
        }
    }

}

void UngroupCommnad::execute() {
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
    this->model->getModel()->remove(target);
    for (auto e : contents) {
        this->model->getModel()->add(e);
    }
}

void UngroupCommnad::unexecute() {
    model->getModel()->clear();
    for (auto e : executeBackup) {
        model->getModel()->add(e);
    }
}
