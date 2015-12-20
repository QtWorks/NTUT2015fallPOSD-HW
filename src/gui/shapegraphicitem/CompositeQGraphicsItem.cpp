//
// Created by Raccoon on 2015/12/11.
//

#include "CompositeQGraphicsItem.h"

void CompositeQGraphicsItem::draw(QPainter *painter) {
    painter->drawRect(boundingbox());
}

QRectF CompositeQGraphicsItem::boundingbox() const {
    if (!this->scene()) {
        return QRectF(cg->getBoundingBox().getX() - _relativeX, cg->getBoundingBox().getY() - _relativeY,
                      this->cg->getBoundingBox().getWidth(), this->cg->getBoundingBox().getHeight());
    }
    return QRectF(_x, _y, this->cg->getBoundingBox().getWidth(), this->cg->getBoundingBox().getHeight());
}

void CompositeQGraphicsItem::dragDraw(QPainter *painter) {
    painter->drawRect(dragBoundingbox());
}

QRectF CompositeQGraphicsItem::dragBoundingbox() const {
    return QRectF(_dragX, _dragY, this->cg->getBoundingBox().getWidth(), this->cg->getBoundingBox().getHeight());
}


CompositeQGraphicsItem::CompositeQGraphicsItem() : ShapeQGraphicsItem() { }

CompositeQGraphicsItem::CompositeQGraphicsItem(Graphics *g) : ShapeQGraphicsItem(g) {
    this->setGraphics(g);
}

void CompositeQGraphicsItem::setGraphics(Graphics *g) {
    ShapeQGraphicsItem::setGraphics(g);
    this->cg = static_cast<CompositeGraphics *>(g);
    this->setPos(this->cg->getBoundingBox().getX(), this->cg->getBoundingBox().getY());
}

void CompositeQGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    for (auto c : childs) {
        painter->translate(this->boundingbox().x(), this->boundingbox().y());
        c->paint(painter, option, widget);
        painter->translate(-this->boundingbox().x(), -this->boundingbox().y());
    }
    painter->setBrush(Qt::transparent);
    ShapeQGraphicsItem::paint(painter, option, widget);
}

void CompositeQGraphicsItem::notifyMove(int x, int y) {
    if (!this->scene()) {
        _relativeX += x;
        _relativeY += y;
    }
    for (auto c : childs) {
        c->notifyMove(x, y);
    }
}
