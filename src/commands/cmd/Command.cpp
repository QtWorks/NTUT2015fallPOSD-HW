//
// Created by Raccoon on 2015/12/11.
//

#include "Command.h"

Command::Command() {

}

Command::~Command() {

}

Command::Command(DrawingWindow *d) {
    this->w = d;
}
