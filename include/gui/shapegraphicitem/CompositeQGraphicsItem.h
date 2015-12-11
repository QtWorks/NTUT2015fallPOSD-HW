//
// Created by Raccoon on 2015/12/11.
//

#ifndef POSD_104598003_HW5_COMPOSITEQGRAPHICSITEM_H
#define POSD_104598003_HW5_COMPOSITEQGRAPHICSITEM_H

#include <vector>
#include "ShapeQGraphicsItem.h"
#include "compositegraphics.h"
#include "boundingbox.h"

using std::vector;

class CompositeQGraphicsItem : public ShapeQGraphicsItem {

public:
    CompositeQGraphicsItem();
    CompositeQGraphicsItem(Graphics *g);

    virtual void setGraphics(Graphics *g) override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF dragBoundingbox() const override;

    vector<ShapeQGraphicsItem *> childs;
protected:
    virtual void draw(QPainter *painter) override;
    virtual QRectF boundingbox() const override;
    virtual void dragDraw(QPainter *painter) override;
private:
    CompositeGraphics *cg = 0;

};


#endif //POSD_104598003_HW5_COMPOSITEQGRAPHICSITEM_H
