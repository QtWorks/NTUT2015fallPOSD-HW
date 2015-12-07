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

using std::string;
using std::ostringstream;
using std::vector;

class SimpleGraphics;

class CompositeGraphics;

class DescriptionVisitor : public GraphicsVisitor {
private:
    ostringstream _oss;
    std::vector<int> _level;

public:
    virtual void visitSimpleGraphic(SimpleGraphics *simpleGraphics);

    virtual void visitCompositeGraphic(CompositeGraphics *compositeGraphics);

    string getDescription();
};

#endif