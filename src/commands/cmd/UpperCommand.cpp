//
// Created by Raccoon on 2016/1/5.
//

#include "UpperCommand.h"

void UpperCommand::execute() {

    if (executeBackup.empty()) {
        // backup
        for (auto e : parent->_graphics) {
            executeBackup.push_back(e);
        }
    } else {
        // restore
        parent->_graphics.clear();
        for (auto e : executeBackup) {
            parent->add(e);
        }
    }

    vector<Graphics *>::iterator pre = parent->_graphics.begin();
    vector<Graphics *>::iterator tt = parent->_graphics.begin();

    for (auto child = parent->_graphics.begin();
         child != parent->_graphics.end(); ++child) {
        if ((*child) == target) {
            tt = child;
            break;
        }
        pre = child;
    }
    if (pre != tt) {
        iter_swap(pre, tt);
    }
}

void UpperCommand::unexecute() {
// restore
    parent->_graphics.clear();
    for (auto e : executeBackup) {
        parent->add(e);
    }
}

UpperCommand::UpperCommand(Graphics *target, CompositeGraphics *parent) {
    this->target = target;
    this->parent = parent;
}
