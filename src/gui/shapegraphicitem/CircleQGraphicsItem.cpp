#include "gui/shapegraphicitem/CircleQGraphicsItem.h"
#include "circle.h"
#include <cmath>

void CircleQGraphicsItem::setGraphics(Graphics *g) {
    ShapeQGraphicsItem::setGraphics(g);
    this->sg = static_cast<SimpleGraphics *>(this->_graphics);
    this->c = static_cast<Circle *>(this->sg->getShape());
    this->setPos(c->getX() - c->getRadius(), c->getY() - c->getRadius());
}

void CircleQGraphicsItem::draw(QPainter *painter) {
    painter->setBrush(Qt::blue);
    painter->drawEllipse(boundingbox());
}

void CircleQGraphicsItem::dragDraw(QPainter *painter) {
    painter->drawEllipse(dragBoundingbox());
}

QRectF CircleQGraphicsItem::boundingbox() const {
    if (!this->scene()) {
        if (c) {
            return QRectF(c->getX() - c->getRadius() - _relativeX, c->getY() - c->getRadius() - _relativeY,
                          c->getRadius() * 2, c->getRadius() * 2);
        }
    }
    if (c) {
        return QRectF(_x, _y, c->getRadius() * 2, c->getRadius() * 2);
    }
    return QRectF(_x, _y, 100, 100);
}

QRectF CircleQGraphicsItem::dragBoundingbox() const {
    if (c) {
        return QRectF(_dragX, _dragY, c->getRadius() * 2, c->getRadius() * 2);
    }
    return QRectF(_dragX, _dragY, 100, 100);
}

CircleQGraphicsItem::CircleQGraphicsItem() : ShapeQGraphicsItem() {
    this->setPos(0, 0);
}

void CircleQGraphicsItem::notifyMove(int x, int y) {
    if (c) {
        this->c->moveBy(x, y);
    }
    if (!this->scene()) {
        _relativeX += x;
        _relativeY += y;
    }
}

bool CircleQGraphicsItem::isCollision(int x, int y) {
    int cx = static_cast<SimpleGraphics *>(this->_graphics)->getShape()->getX();
    int cy = static_cast<SimpleGraphics *>(this->_graphics)->getShape()->getY();
    int r = static_cast<Circle *>( static_cast<SimpleGraphics *>(this->_graphics)->getShape())->getRadius();
    return pow((x - cx), 2) + pow((y - cy), 2) < pow(r, 2);
}
