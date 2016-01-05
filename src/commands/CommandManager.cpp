//
// Created by Raccoon on 2015/12/11.
//

#include "CommandManager.h"
#include "CreateCircleCommand.h"
#include "CreateRectangleCommand.h"
#include "CreateSquareCommand.h"
#include "GroupCommand.h"
#include "UngroupCommnad.h"
#include "DeleteCommand.h"
#include "UpperCommand.h"
#include "LowerCommand.h"
#include "MoveCommand.h"

CommandManager::CommandManager(DrawingController *ctrl, GraphicsModel *m) {
    this->controller = ctrl;
    this->model = m;
}

CommandManager::~CommandManager() {

}

void CommandManager::undo() {
    if (!this->canUndo())return;

    Command *cmd = this->undoCommands.top();
    this->undoCommands.pop();
    cmd->unexecute();
    this->redoCommands.push(cmd);
}

void CommandManager::redo() {
    if (!this->canRedo())return;

    Command *cmd = this->redoCommands.top();
    this->redoCommands.pop();
    cmd->execute();
    this->undoCommands.push(cmd);
}

void CommandManager::createSquare() {
    Command *cmd = new CreateSquareCommand(this->model);
    this->executeCommand(cmd);
}

void CommandManager::createCircle() {
    Command *cmd = new CreateCircleCommand(this->model);
    this->executeCommand(cmd);
}

void CommandManager::createRectangle() {
    Command *cmd = new CreateRectangleCommand(this->model);
    this->executeCommand(cmd);
}

void CommandManager::deleteSimpleGraphic() {
    Command *cmd = new DeleteCommand(model, controller->getGraphicsItems());
    this->executeCommand(cmd);
}

void CommandManager::group() {
    Command *cmd = new GroupCommand(model, controller->getGraphicsItems());
    this->executeCommand(cmd);
}

void CommandManager::ungroup() {
    Command *cmd = new UngroupCommnad(model, controller->getGraphicsItems());
    this->executeCommand(cmd);
}

void CommandManager::move(ShapeQGraphicsItem *item, int diffX, int diffY) {
    Command *cmd = new MoveCommand(item, diffX, diffY);
    this->executeCommand(cmd);
}

void CommandManager::upperLayer() {
    Command *cmd = new UpperCommand(controller->getSelectedTarget(), controller->getSelectedParent());
    this->executeCommand(cmd);
}

void CommandManager::lowerLayer() {
    Command *cmd = new LowerCommand(controller->getSelectedTarget(), controller->getSelectedParent());
    this->executeCommand(cmd);
}

/**
 * State Method
 */

bool CommandManager::canUndo() {
    return !this->undoCommands.empty();
}

bool CommandManager::canRedo() {
    return !this->redoCommands.empty();
}

void CommandManager::executeCommand(Command *command) {
    command->execute();
    this->undoCommands.push(command);

    this->clearRedos();
}

void CommandManager::clearRedos() {
    while (!this->redoCommands.empty()) {
        Command *cmd = this->redoCommands.top();
        this->redoCommands.pop();
        delete cmd;
    }
}

void CommandManager::clear() {
    while (!undoCommands.empty())undoCommands.pop();
    while (!redoCommands.empty())redoCommands.pop();
}
