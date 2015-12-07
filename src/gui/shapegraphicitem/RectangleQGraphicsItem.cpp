#include "gui/shapegraphicitem/RectangleQGraphicsItem.h"

void RectangleQGraphicsItem::draw(QPainter *painter)
{
    painter->drawRect(_x, _y, 200, 100);
}
void RectangleQGraphicsItem::dragDraw(QPainter *painter)
{
    painter->drawRect(_dragX, _dragY, 200, 100);
}
QRectF RectangleQGraphicsItem::boundingbox() const
{
    return QRectF(_x, _y, 200, 100);
}
QRectF RectangleQGraphicsItem::dragBoundingbox() const
{
    return QRectF(_dragX, _dragY, 200, 100);
}