//
// Created by Raccoon on 2015/12/7.
//

#ifndef INC_104598003_HW5_CIRCLEQGRAPHICITEM_H
#define INC_104598003_HW5_CIRCLEQGRAPHICITEM_H

#include "gui/shapegraphicitem/ShapeQGraphicsItem.h"

class CircleQGraphicsItem: public ShapeQGraphicsItem
{
public:

    CircleQGraphicsItem()
        : ShapeQGraphicsItem()
    {
        this->setPos(-800,-100);
    }
    virtual void draw(QPainter *painter) override;
    virtual void dragDraw(QPainter *painter) override;
    virtual QRectF boundingbox() const override;
    virtual QRectF dragBoundingbox() const override;

private:

};

#endif //INC_104598003_HW5_CIRCLEQGRAPHICITEM_H
