#include "gui/shapegraphicitem/SquareQGraphicsItem.h"

void SquareQGraphicsItem::draw(QPainter *painter)
{
    painter->drawRect(_x, _y, 100, 100);
}

void SquareQGraphicsItem::dragDraw(QPainter *painter)
{
    painter->drawRect(_dragX, _dragY, 100, 100);
}

QRectF SquareQGraphicsItem::boundingbox() const
{
    return QRectF(_x, _y, 100, 100);
}

QRectF SquareQGraphicsItem::dragBoundingbox() const
{
    return QRectF(_dragX, _dragY, 100, 100);
}