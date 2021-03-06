//
// Created by Raccoon on 2015/12/7.
//

#ifndef INC_104598003_HW5_SQUAREQGRAPHICITEM_H
#define INC_104598003_HW5_SQUAREQGRAPHICITEM_H

#include "square.h"
#include "simplegraphics.h"
#include "ShapeQGraphicsItem.h"

class SquareQGraphicsItem : public ShapeQGraphicsItem {

public:

    SquareQGraphicsItem() : ShapeQGraphicsItem() { }

    SquareQGraphicsItem(Graphics *g) : ShapeQGraphicsItem() {
        this->setGraphics(g);
    }

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
    Square *s = 0;
};

#endif //INC_104598003_HW5_SQUAREQGRAPHICITEM_H
