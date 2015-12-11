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

class QtGraphicsViewVisitor : public GraphicsVisitor {

public:

    QtGraphicsViewVisitor(QGraphicsScene *scene);

    virtual void visitSimpleGraphic(SimpleGraphics *graphics) override;
    virtual void visitCompositeGraphic(CompositeGraphics *graphics) override;


    virtual void visitRootGraphic(RootGraphics *graphics);
private:

    QPen *greenPen;
    QPen *bluePen;

    QGraphicsScene *scene;
    void drawCircle(Circle &shape);
    void drawRectangle(Rectangle &shape);
    void drawSquare(Square &shape);
    void drawBoundingBox(BoundingBox &boundingBox);
};


#endif
