#ifndef QTGRAPHICSVIEWVISITOR_H
#define QTGRAPHICSVIEWVISITOR_H

#include <QGraphicsScene>
#include <QColor>
#include "GraphicsVisitor.h"
#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "square.h"
#include "boundingbox.h"
#include <stack>
#include <include/gui/shapegraphicitem/CompositeQGraphicsItem.h>

class DrawingWindow;

using std::stack;

class QtGraphicsViewVisitor : public GraphicsVisitor {

public:

    QtGraphicsViewVisitor(QGraphicsScene *scene);

    DrawingWindow *w;

    virtual void visitSimpleGraphic(SimpleGraphics *graphics) override;
    virtual void visitCompositeGraphic(CompositeGraphics *graphics) override;
    virtual void visitRootGraphic(RootGraphics *graphics);

    virtual void enter() override;
    virtual void leave() override;
    void draw();
private:

    QPen *greenPen;
    QPen *bluePen;

    stack<CompositeQGraphicsItem *> v;
    stack<ShapeQGraphicsItem *> rootItem;

    QGraphicsScene *scene;
    void drawCircle(Circle &shape);
    void drawRectangle(Rectangle &shape);
    void drawSquare(Square &shape);
    void drawBoundingBox(BoundingBox &boundingBox);
};


#endif
