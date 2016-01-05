#ifndef INC_104598003_HW5_SHAPEQGRAPHICSITEM_H
#define INC_104598003_HW5_SHAPEQGRAPHICSITEM_H

#include "graphics.h"
#include "DrawingController.h"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QPainter>

#include <iostream>
using namespace std;

class ShapeQGraphicsItem : public QGraphicsItem {
public:
    ShapeQGraphicsItem();
    ShapeQGraphicsItem(Graphics *g);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override final;

    virtual void setGraphics(Graphics *g);
    virtual Graphics *getGraphics();

    bool isDragable() const;

    void setDragable(bool _dragable);
    void setPen(QPen &pen);

    virtual bool isCollision(int x, int y);

    DrawingController *controller;

    int _relativeX = 0;
    int _relativeY = 0;

    virtual void notifyMove(int diffX, int diffY);

    Graphics *_graphics = 0;

protected:

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
    bool _dragable = true;
    int _dragX;
    int _dragY;


    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    QPen _pen;
    QPen _selectedPen;

private:

};

#endif