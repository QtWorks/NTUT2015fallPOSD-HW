#include "QtGraphicsViewVisitor.h"

#include "simplegraphics.h"
#include "compositegraphics.h"

using namespace std;

QtGraphicsViewVisitor::QtGraphicsViewVisitor(QGraphicsScene *scene)
        : GraphicsVisitor(), scene(scene) {
    greenPen = new QPen(Qt::green);
    bluePen = new QPen(Qt::blue);

}

void QtGraphicsViewVisitor::visitSimpleGraphic(SimpleGraphics *graphics) {
    Shape *shape = graphics->getShape();
    string describe = shape->describe();

    if (describe[0] == 'R') {
        drawRectangle(*static_cast<Rectangle *>(shape));
    } else if (describe[0] == 'S') {
        drawSquare(*static_cast<Square *>(shape));
    } else if (describe[0] == 'C') {
        drawCircle(*static_cast<Circle *>(shape));
    }
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
