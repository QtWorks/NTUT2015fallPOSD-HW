//
// Created by Raccoon on 2015/12/7.
//

#ifndef INC_104598003_HW5_CIRCLEQGRAPHICITEM_H
#define INC_104598003_HW5_CIRCLEQGRAPHICITEM_H

#include "gui/shapegraphicitem/ShapeQGraphicsItem.h"
#include "circle.h"
#include "simplegraphics.h"

class CircleQGraphicsItem : public ShapeQGraphicsItem {
public:
    CircleQGraphicsItem();
    CircleQGraphicsItem(Graphics *g) : ShapeQGraphicsItem() {
        this->setGraphics(g);
    }

    virtual void setGraphics(Graphics *g) override;
    virtual void draw(QPainter *painter) override;
    virtual void dragDraw(QPainter *painter) override;
    virtual QRectF boundingbox() const override;
    virtual QRectF dragBoundingbox() const override;
    virtual void notifyMove(int x, int y) override;

    virtual bool isCollision(int x, int y) override;
protected:

private:
    SimpleGraphics *sg = 0;
    Circle *c = 0;
};

#endif //INC_104598003_HW5_CIRCLEQGRAPHICITEM_H
