#include "QtGraphicsViewVisitor.h"

#include "simplegraphics.h"
#include "compositegraphics.h"

#include "gui/shapegraphicitem/CircleQGraphicsItem.h"
#include "gui/shapegraphicitem/RectangleQGraphicsItem.h"
#include "gui/shapegraphicitem/SquareQGraphicsItem.h"
#include "gui/shapegraphicitem/CompositeQGraphicsItem.h"

using namespace std;

QtGraphicsViewVisitor::QtGraphicsViewVisitor(QGraphicsScene *scene)
        : GraphicsVisitor(), scene(scene) {
    greenPen = new QPen(Qt::green);
    greenPen->setWidth(greenPen->width()*2);
    bluePen = new QPen(Qt::blue);
    bluePen->setWidth(bluePen->width()*2);

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
    scene->addItem(item);
}

void QtGraphicsViewVisitor::visitRootGraphic(RootGraphics *graphics) {
    
}

void QtGraphicsViewVisitor::visitCompositeGraphic(CompositeGraphics *graphics) {
    BoundingBox a = graphics->getBoundingBox();
    this->drawBoundingBox(a);
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
