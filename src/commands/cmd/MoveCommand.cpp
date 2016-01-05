//
// Created by Raccoon on 2016/1/6.
//

#include "MoveCommand.h"
#include "MoveVisitor.h"


MoveCommand::MoveCommand(ShapeQGraphicsItem *item, int diffX, int diffY) {
    target = item->getGraphics();
    this->diff_x = diffX;
    this->diff_y = diffY;
}

void MoveCommand::execute() {
    MoveVisitor visitor(diff_x, diff_y);
    target->accept(visitor);
}

void MoveCommand::unexecute() {
    MoveVisitor visitor(-diff_x, -diff_y);
    target->accept(visitor);
}

