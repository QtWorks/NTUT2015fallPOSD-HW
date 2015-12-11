#include "gui/shapegraphicitem/RectangleQGraphicsItem.h"

void RectangleQGraphicsItem::draw(QPainter *painter) {
    painter->drawRect(boundingbox());
}

void RectangleQGraphicsItem::dragDraw(QPainter *painter) {
    painter->drawRect(dragBoundingbox());
}

QRectF RectangleQGraphicsItem::boundingbox() const {
    if (r) {
        return QRectF(_x, _y, this->r->getWidth(), this->r->getHeight());
    }
    return QRectF(_x, _y, 200, 100);
}

QRectF RectangleQGraphicsItem::dragBoundingbox() const {
    if (r) {
        return QRectF(_dragX, _dragY, this->r->getWidth(), this->r->getHeight());
    }
    return QRectF(_dragX, _dragY, 200, 100);
}

void RectangleQGraphicsItem::setGraphics(Graphics *g) {
    ShapeQGraphicsItem::setGraphics(g);
    this->sg = static_cast<SimpleGraphics *>(this->_graphics);
    this->r = static_cast<Rectangle *>(this->sg->getShape());
    this->setPos(r->getX(), r->getY());
}

void RectangleQGraphicsItem::notifyMove(int x, int y) {
    this->r->moveBy(x, y);
}
