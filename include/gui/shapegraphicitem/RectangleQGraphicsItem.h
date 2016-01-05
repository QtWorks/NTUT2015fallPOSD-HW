//
// Created by Raccoon on 2015/12/7.
//

#ifndef INC_104598003_HW5_RECTANGLEQGRAPHICITEM_H
#define INC_104598003_HW5_RECTANGLEQGRAPHICITEM_H

#include "rectangle.h"
#include "simplegraphics.h"
#include "ShapeQGraphicsItem.h"

class RectangleQGraphicsItem : public ShapeQGraphicsItem {

public:
    RectangleQGraphicsItem(Graphics *g) : ShapeQGraphicsItem() {
        this->setGraphics(g);
    }

    RectangleQGraphicsItem() : ShapeQGraphicsItem() { }

public:
    virtual void draw(QPainter *painter) override;
    virtual void dragDraw(QPainter *painter) override;
    virtual QRectF boundingbox() const override;
    virtual QRectF dragBoundingbox() const override;
    virtual void setGraphics(Graphics *g) override;
    virtual void notifyMove(int diffX, int diffY) override;

    virtual bool isCollision(int x, int y) override;
protected:

private:
    SimpleGraphics *sg = 0;
    Rectangle *r = 0;

};

#endif //INC_104598003_HW5_RECTANGLEQGRAPHICITEM_H