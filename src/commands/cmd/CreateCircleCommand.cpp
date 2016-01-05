//
// Created by Raccoon on 2016/1/5.
//

#include "CreateCircleCommand.h"
#include "RootGraphics.h"
#include "circle.h"


void CreateCircleCommand::execute() {
    if (!circle) {
        circle = new SimpleGraphics(new Circle(0, 0, 50));
    }
    root->add(circle);
}

void CreateCircleCommand::unexecute() {
    root->remove(circle);
}

CreateCircleCommand::CreateCircleCommand(GraphicsModel *m) {
    model = m;
    root = model->getModel();
}

CreateCircleCommand::~CreateCircleCommand() {
    delete circle;
    circle = 0;
}
