//
// Created by Raccoon on 2015/10/19.
//

#ifndef DESCRIPTIONVISITOR_H
#define DESCRIPTIONVISITOR_H

#include "GraphicsVisitor.h"
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <stack>

using std::string;
using std::ostringstream;
using std::vector;
using std::stack;

class SimpleGraphics;

class CompositeGraphics;

class DescriptionVisitor : public GraphicsVisitor {
private:
    ostringstream _oss;
    std::vector<int> _level;

    std::stack<string> level;

    std::string prefix = "";

public:
    virtual void visitSimpleGraphic(SimpleGraphics *simpleGraphics) override;
    virtual void visitCompositeGraphic(CompositeGraphics *compositeGraphics) override;
    virtual void enter() override;
    virtual void leave() override;
    void printPrefix();
    string getDescription();
};

#endif