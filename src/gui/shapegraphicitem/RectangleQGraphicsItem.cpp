#include "RectangleQGraphicsItem.h"

void RectangleQGraphicsItem::draw(QPainter *painter) {
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingbox());
}

void RectangleQGraphicsItem::dragDraw(QPainter *painter) {
    painter->drawRect(dragBoundingbox());
}

QRectF RectangleQGraphicsItem::boundingbox() const {
    if (r) {
        if (!this->scene()) {
            return QRectF(r->getX() - _relativeX, r->getY() - _relativeY, this->r->getWidth(), this->r->getHeight());
        }
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

void RectangleQGraphicsItem::notifyMove(int diffX, int diffY) {
    this->r->moveBy(diffX, diffY);
    if (!this->scene()) {
        _relativeX += diffX;
        _relativeY += diffY;
    }
    ShapeQGraphicsItem::notifyMove(diffX, diffY);
}

bool RectangleQGraphicsItem::isCollision(int x, int y) {
    Rectangle* r = static_cast<Rectangle *>(static_cast<SimpleGraphics *>(this->_graphics)->getShape());
    int llx = r->getX();
    int lly = r->getY();
    int h = r->getHeight();
    int w = r->getWidth();
    return !(x < llx || x > llx + w || y < lly || y > lly + h);
}
