#include "gui/shapegraphicitem/CircleQGraphicsItem.h"

void CircleQGraphicsItem::draw(QPainter *painter)
{
    painter->drawEllipse(_x, _y, 100, 100);
}

QRectF CircleQGraphicsItem::boundingbox() const
{
    return QRectF(_x, _y, 100, 100);
}

void CircleQGraphicsItem::dragDraw(QPainter *painter)
{
    painter->drawEllipse(_dragX,_dragY, 100, 100);
}

QRectF CircleQGraphicsItem::dragBoundingbox() const
{
    return QRectF(_dragX,_dragY, 100, 100);
}