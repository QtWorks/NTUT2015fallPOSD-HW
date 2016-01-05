//
// Created by Raccoon on 2016/1/5.
//

#include "CreateSquareCommand.h"
#include "square.h"

CreateSquareCommand::CreateSquareCommand(GraphicsModel *m) {
    model = m;
    root = model->getModel();
}

CreateSquareCommand::~CreateSquareCommand() {
    delete square;
}

void CreateSquareCommand::execute() {
    if (!square) {
        square = new SimpleGraphics(new Square(0, 0, 100));
    }
    root->add(square);
}

void CreateSquareCommand::unexecute() {
    root->remove(square);
}
