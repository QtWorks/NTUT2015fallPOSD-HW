#include "DescriptionVisitor.h"
#include "compositegraphics.h"
#include "simplegraphics.h"

void DescriptionVisitor::visitSimpleGraphic(SimpleGraphics *simpleGraphics) {
    int space = _level.size();
    for (int i = 0; i < space; i++) {
        this->_oss << "  ";
    }
    this->_oss << simpleGraphics->getShape()->describe() << "\n";

    if (_level.size() > 0) {
        if (--_level[_level.size() - 1] == 0) {
            _level.pop_back();
        }
    }
}

void DescriptionVisitor::visitCompositeGraphic(CompositeGraphics *compositeGraphics) {
    int space = _level.size();
    for (int i = 0; i < space; i++) {
        this->_oss << "  ";
    }
    this->_oss << "Comp " << compositeGraphics->getBoundingBox().describe() << "\n";
    _level.push_back(compositeGraphics->size());
}

string DescriptionVisitor::getDescription() {
    return this->_oss.str();
}