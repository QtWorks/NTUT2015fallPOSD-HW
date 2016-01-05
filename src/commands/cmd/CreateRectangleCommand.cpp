//
// Created by Raccoon on 2016/1/5.
//

#include "CreateRectangleCommand.h"

CreateRectangleCommand::CreateRectangleCommand(GraphicsModel *m) {
    model = m;
    root = model->getModel();
}

CreateRectangleCommand::~CreateRectangleCommand() {
    delete rectangle;
    rectangle = 0;
}

void CreateRectangleCommand::execute() {
    if (!rectangle) {
        rectangle = new SimpleGraphics(new Rectangle(0, 0, 300, 150));
    }
    root->add(rectangle);
}

void CreateRectangleCommand::unexecute() {
    root->remove(rectangle);
}
