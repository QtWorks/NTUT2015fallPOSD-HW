//
// Created by Raccoon on 2015/12/22.
//

#include "QtGraphicsToStandardItemModelVisitor.h"
#include "simplegraphics.h"
#include "compositegraphics.h"
#include "graphics.h"

#include <string>
#include <QString>

using namespace std;

QtGraphicsToStandardItemModelVisitor::QtGraphicsToStandardItemModelVisitor() {
    this->model = new QStandardItemModel;
    this->_itemStack = new stack<QStandardItem *>();

    this->_itemStack->push(model->invisibleRootItem());

    circleIcon = new QIcon("./icon/circle.png");
    squareIcon = new QIcon("./icon/square.png");
    rectangleIcon = new QIcon("./icon/rectangle.png");
    compositeIcon = new QIcon("./icon/composite.png");
}

QtGraphicsToStandardItemModelVisitor::~QtGraphicsToStandardItemModelVisitor() {
    delete _itemStack;
}

void QtGraphicsToStandardItemModelVisitor::visitSimpleGraphic(SimpleGraphics *graphics) {
    string name = graphics->getShape()->describe();
    char shape = name[0];
    if (graphics->isSelected) {
        name.insert(0 , "*");
    }
    QStandardItem *item;
    switch (shape) {
        case 'C':
            item = new QStandardItem(*circleIcon, QString(name.c_str()));
            break;
        case 'R':
            item = new QStandardItem(*rectangleIcon, QString(name.c_str()));
            break;
        case 'S':
            item = new QStandardItem(*squareIcon, QString(name.c_str()));
            break;
    }
    this->_itemStack->top()->appendRow(item);
}

void QtGraphicsToStandardItemModelVisitor::visitCompositeGraphic(CompositeGraphics *graphics) {
    string name = "Comp " + graphics->getBoundingBox().describe();
    if (graphics->isSelected) {
        name.insert(0, "*");
    }
    QStandardItem *item = new QStandardItem(*compositeIcon, QString(name.c_str()));
    this->_itemStack->push(item);
}

void QtGraphicsToStandardItemModelVisitor::visitRootGraphic(RootGraphics *graphics) {

}

void QtGraphicsToStandardItemModelVisitor::enter() {
    GraphicsVisitor::enter();
}

void QtGraphicsToStandardItemModelVisitor::leave() {

    QStandardItem *item = static_cast<QStandardItem *>(this->_itemStack->top());

    if (this->_itemStack->size() > 1) {
        this->_itemStack->pop();
        this->_itemStack->top()->appendRow(item);
    }
    GraphicsVisitor::leave();
}

QStandardItemModel *QtGraphicsToStandardItemModelVisitor::getModel() {
    return model;
}
