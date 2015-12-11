#include "gui/shapegraphicitem/SquareQGraphicsItem.h"

void SquareQGraphicsItem::draw(QPainter *painter) {
    painter->drawRect(boundingbox());
}

void SquareQGraphicsItem::dragDraw(QPainter *painter) {
    painter->drawRect(dragBoundingbox());
}

QRectF SquareQGraphicsItem::boundingbox() const {
    if (s) {
        return QRectF(_x, _y, this->s->getLength(), this->s->getLength());
    }
    return QRectF(_x, _y, 100, 100);
}

QRectF SquareQGraphicsItem::dragBoundingbox() const {
    if (s) {
        return QRectF(_dragX, _dragY, this->s->getLength(), this->s->getLength());
    }
    return QRectF(_dragX, _dragY, 100, 100);
}

void SquareQGraphicsItem::setGraphics(Graphics *g) {
    ShapeQGraphicsItem::setGraphics(g);
    this->sg = static_cast<SimpleGraphics *>(this->_graphics);
    this->s = static_cast<Square *>(this->sg->getShape());
    this->setPos(s->getX(), s->getY());
}

void SquareQGraphicsItem::notifyMove(int x, int y) {
    this->s->moveBy(x, y);
}
