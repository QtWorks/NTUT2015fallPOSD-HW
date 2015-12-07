//
// Created by Raccoon on 2015/12/7.
//

#ifndef INC_104598003_HW5_SQUAREQGRAPHICITEM_H
#define INC_104598003_HW5_SQUAREQGRAPHICITEM_H

#include "gui/shapegraphicitem/ShapeQGraphicsItem.h"

class SquareQGraphicsItem: public ShapeQGraphicsItem
{

public:
    virtual void draw(QPainter *painter) override;
    virtual void dragDraw(QPainter *painter) override;
    virtual QRectF boundingbox() const override;
    virtual QRectF dragBoundingbox() const override;

private:

};

#endif //INC_104598003_HW5_SQUAREQGRAPHICITEM_H
