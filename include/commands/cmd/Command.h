//
// Created by Raccoon on 2015/12/11.
//

#ifndef POSD_104598003_HW5_COMMAND_H
#define POSD_104598003_HW5_COMMAND_H

#include "DescriptionVisitor.h"
#include <string>

class DrawingWindow;

using std::string;

class Command {
public:
    Command();
    Command(DrawingWindow *d);

    DrawingWindow *w;
    string checkpoint;

    virtual ~Command();
    virtual void execute() = 0;
    virtual void unexecute() = 0;
};


#endif //POSD_104598003_HW5_COMMAND_H
