//
// Created by Raccoon on 2015/12/11.
//

#include "CompositeQGraphicsItem.h"

void CompositeQGraphicsItem::draw(QPainter *painter) {
    painter->drawRect(boundingbox());
}

QRectF CompositeQGraphicsItem::boundingbox() const {
    return QRectF(_x, _y, this->cg->getBoundingBox().getWidth(), this->cg->getBoundingBox().getHeight());
}

void CompositeQGraphicsItem::dragDraw(QPainter *painter) {
    painter->drawRect(dragBoundingbox());
}

QRectF CompositeQGraphicsItem::dragBoundingbox() const {
    return QRectF(_dragX, _dragY, this->cg->getBoundingBox().getWidth(), this->cg->getBoundingBox().getHeight());
}

void CompositeQGraphicsItem::setGraphics(Graphics *g) {
    ShapeQGraphicsItem::setGraphics(g);
    this->cg = static_cast<CompositeGraphics *>(g);
    this->setPos(this->cg->getBoundingBox().getX(), this->cg->getBoundingBox().getY());
}

CompositeQGraphicsItem::CompositeQGraphicsItem(Graphics *g) : ShapeQGraphicsItem(g) {
    this->setGraphics(g);
}

CompositeQGraphicsItem::CompositeQGraphicsItem() : ShapeQGraphicsItem() { }

void CompositeQGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    for (auto c : childs) {
        c->paint(painter, option, widget);
    }
    ShapeQGraphicsItem::paint(painter, option, widget);
}
