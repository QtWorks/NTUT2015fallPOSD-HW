#include "SquareQGraphicsItem.h"

void SquareQGraphicsItem::draw(QPainter *painter) {
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingbox());
}

void SquareQGraphicsItem::dragDraw(QPainter *painter) {
    painter->drawRect(dragBoundingbox());
}

QRectF SquareQGraphicsItem::boundingbox() const {
    if (!this->scene()) {
        if (s) {
            return QRectF(s->getX() - _relativeX, s->getY() - _relativeY, this->s->getLength(), this->s->getLength());
        }
    }
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

void SquareQGraphicsItem::notifyMove(int diffX, int diffY) {
    this->s->moveBy(diffX, diffY);
    if (!this->scene()) {
        _relativeX += diffX;
        _relativeY += diffY;
    }
    ShapeQGraphicsItem::notifyMove(diffX, diffY);
}

bool SquareQGraphicsItem::isCollision(int x, int y) {
    Square *s = static_cast<Square *>(static_cast<SimpleGraphics *>(this->_graphics)->getShape());
    int llx = s->getX();
    int lly = s->getY();
    int l = s->getLength();
    return !(x < llx || x > llx + l || y < lly || y > lly + l);
}
