//
// Created by Raccoon on 2016/1/5.
//

#include "LowerCommand.h"

#include <utility>
using namespace std;

void LowerCommand::execute() {
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
    reverse_iterator<vector<Graphics *>::iterator> pre = parent->_graphics.rbegin();
    reverse_iterator<vector<Graphics *>::iterator> tt = parent->_graphics.rbegin();

    for (reverse_iterator<vector<Graphics *>::iterator> child = parent->_graphics.rbegin();
         child != parent->_graphics.rend(); ++child) {
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

void LowerCommand::unexecute() {
// restore
    parent->_graphics.clear();
    for (auto e : executeBackup) {
        parent->add(e);
    }
}

LowerCommand::LowerCommand(Graphics *target, CompositeGraphics *parent) {
    this->target = target;
    this->parent = parent;
}
