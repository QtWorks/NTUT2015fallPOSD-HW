#include "QtGraphicsViewVisitor.h"

#include "simplegraphics.h"
#include "compositegraphics.h"

#include "gui/shapegraphicitem/CircleQGraphicsItem.h"
#include "gui/shapegraphicitem/RectangleQGraphicsItem.h"
#include "gui/shapegraphicitem/SquareQGraphicsItem.h"
#include "gui/shapegraphicitem/CompositeQGraphicsItem.h"

#include <stack>

using namespace std;

QtGraphicsViewVisitor::QtGraphicsViewVisitor(QGraphicsScene *scene)
        : GraphicsVisitor(), scene(scene) {
    greenPen = new QPen(Qt::green);
    greenPen->setWidth(greenPen->width() * 2);
    bluePen = new QPen(Qt::black);
    bluePen->setWidth(bluePen->width() * 3);

}

void QtGraphicsViewVisitor::visitSimpleGraphic(SimpleGraphics *graphics) {
    Shape *shape = graphics->getShape();
    string describe = shape->describe();

    ShapeQGraphicsItem *item = 0;

    if (describe[0] == 'R') {
        item = new RectangleQGraphicsItem(graphics);
    } else if (describe[0] == 'S') {
        item = new SquareQGraphicsItem(graphics);
    } else if (describe[0] == 'C') {
        item = new CircleQGraphicsItem(graphics);
    }
    item->setPen(*bluePen);
    item->w = this->w;

    if (v.empty()) {
//        scene->addItem(item);
        this->rootItem.push(item);
    } else {
        item->_relativeX = static_cast<CompositeQGraphicsItem *>(v.top())->getGraphics()->getBoundingBox().getX();
        item->_relativeY = static_cast<CompositeQGraphicsItem *>(v.top())->getGraphics()->getBoundingBox().getY();

        CompositeQGraphicsItem *i = static_cast<CompositeQGraphicsItem *>(v.top());
        i->childs.insert(i->childs.begin(), item);
//        static_cast<CompositeQGraphicsItem *>(v.top())->childs.push_back(item);
    }
}

void QtGraphicsViewVisitor::visitRootGraphic(RootGraphics *graphics) {

}

void QtGraphicsViewVisitor::visitCompositeGraphic(CompositeGraphics *graphics) {
    CompositeQGraphicsItem *cqg = new CompositeQGraphicsItem(graphics);
    cqg->_relativeX = graphics->getBoundingBox().getX();
    cqg->_relativeY = graphics->getBoundingBox().getY();
    cqg->setPen(*greenPen);
    cqg->w = this->w;
    v.push(cqg);
}

void QtGraphicsViewVisitor::drawCircle(Circle &shape) {
    int x = shape.getX();
    int y = shape.getY();
    int r = shape.getRadius();
    scene->addEllipse(x - r, y - r, r * 2, r * 2, *bluePen);
}

void QtGraphicsViewVisitor::drawRectangle(Rectangle &shape) {
    int x = shape.getX();
    int y = shape.getY();
    int w = shape.getWidth();
    int h = shape.getHeight();
    scene->addRect(x, y, w, h, *bluePen);
}

void QtGraphicsViewVisitor::drawSquare(Square &shape) {
    int x = shape.getX();
    int y = shape.getY();
    int l = shape.getLength();
    scene->addRect(x, y, l, l, *bluePen);
}

void QtGraphicsViewVisitor::drawBoundingBox(BoundingBox &boundingBox) {
    int x = boundingBox.getX();
    int y = boundingBox.getY();
    int w = boundingBox.getWidth();
    int h = boundingBox.getHeight();
    scene->addRect(x, y, w, h, *greenPen);
}

void QtGraphicsViewVisitor::enter() {
    GraphicsVisitor::enter();
}

void QtGraphicsViewVisitor::leave() {
    CompositeQGraphicsItem *q = static_cast<CompositeQGraphicsItem *>(v.top());
    v.pop();
    if (!v.empty()) {
        q->_relativeX = static_cast<CompositeQGraphicsItem *>(v.top())->getGraphics()->getBoundingBox().getX();
        q->_relativeY = static_cast<CompositeQGraphicsItem *>(v.top())->getGraphics()->getBoundingBox().getY();
        CompositeQGraphicsItem *i = static_cast<CompositeQGraphicsItem *>(v.top());
        i->childs.insert(i->childs.begin(), q);
//        static_cast<CompositeQGraphicsItem *>(v.top())->childs.push_back(q);
    } else {
        q->_relativeX = 0;
        q->_relativeY = 0;
        rootItem.push(q);
//        scene->addItem(q);
    }
}

void QtGraphicsViewVisitor::draw() {
    while (!rootItem.empty()){
        scene->addItem(rootItem.top());
        rootItem.pop();
    }
}
