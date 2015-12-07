#ifndef INC_104598003_HW5_SHAPEQGRAPHICSITEM_H
#define INC_104598003_HW5_SHAPEQGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QPainter>
#include <iostream>

#include "graphics/graphics.h"

using namespace std;

class ShapeQGraphicsItem: public QGraphicsItem
{
public:
    ShapeQGraphicsItem();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override final;
    virtual QRectF boundingRect() const override final;

    void setPen(QPen &pen);

protected:
    QPen _pen;

    int _x;
    int _y;

    /**
     * Template method
     */
    virtual void draw(QPainter *painter) = 0;
    virtual QRectF boundingbox() const = 0;
    virtual void dragDraw(QPainter *painter) = 0;
    virtual QRectF dragBoundingbox() const = 0;

    /**
     * Provider feature that mouse drag to move the item
     */
    QPointF _dragStart;
    bool _isDraging = false;
    int _dragX;
    int _dragY;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override final;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override final;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override final;
};

#endif