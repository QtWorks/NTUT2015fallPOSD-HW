//
// Created by Raccoon on 2015/12/11.
//

#ifndef POSD_104598003_HW5_COMMANDMANAGER_H
#define POSD_104598003_HW5_COMMANDMANAGER_H

#include "Command.h"
#include "DrawingController.h"
#include "GraphicsModel.h"

#include <stack>
using std::stack;

class CommandManager {
public:
    CommandManager(DrawingController*ctrl, GraphicsModel *m);
    ~CommandManager();
    void undo();
    void redo();
    void createSquare();
    void createCircle();
    void createRectangle();
    void deleteSimpleGraphic();
    void group();
    void ungroup();
    void upperLayer();
    void lowerLayer();

    void clear();

    bool canUndo();
    bool canRedo();

    void move(ShapeQGraphicsItem *item, int diffX, int diffY);

private:
    void executeCommand(Command *);
private:
    GraphicsModel *model;
    DrawingController *controller;
    stack<Command *> undoCommands;
    stack<Command *> redoCommands;

    void clearRedos();
};


#endif //POSD_104598003_HW5_COMMANDMANAGER_H
