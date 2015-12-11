#include "DescriptionVisitor.h"
#include "compositegraphics.h"
#include "simplegraphics.h"

void DescriptionVisitor::visitSimpleGraphic(SimpleGraphics *simpleGraphics) {
    this->printPrefix();
    this->_oss << simpleGraphics->getShape()->describe() << "\n";
}

void DescriptionVisitor::visitCompositeGraphic(CompositeGraphics *compositeGraphics) {
    this->printPrefix();
    this->_oss << "Comp " << compositeGraphics->getBoundingBox().describe() << "\n";
}

string DescriptionVisitor::getDescription() {
    return this->_oss.str();
}

void DescriptionVisitor::enter() {
    prefix += "  ";
}

void DescriptionVisitor::leave() {
    if (prefix.length() >= 2) {
        prefix.pop_back();
        prefix.pop_back();
    } else {
        throw string("operation not valided.");
    }
}

void DescriptionVisitor::printPrefix() {
    _oss << prefix;
}

void DescriptionVisitor::visitRootGraphic(RootGraphics *graphics) {

}
