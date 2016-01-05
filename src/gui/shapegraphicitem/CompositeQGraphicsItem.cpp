//
// Created by Raccoon on 2015/12/11.
//

#include "CompositeQGraphicsItem.h"
#include "simplegraphics.h"

#include <iterator>

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
    if (!isSelected()) {
        for (auto c : childs) {
            c->setSelected(false);
        }
    }
    for (auto c : childs) {
        painter->translate(this->boundingbox().x(), this->boundingbox().y());
        c->paint(painter, option, widget);
        painter->translate(-this->boundingbox().x(), -this->boundingbox().y());
    }
    painter->setBrush(Qt::NoBrush);
    ShapeQGraphicsItem::paint(painter, option, widget);
}

void CompositeQGraphicsItem::notifyMove(int diffX, int diffY) {
    if (!this->scene()) {
        _relativeX += diffX;
        _relativeY += diffY;
    }
    for (auto c : childs) {
        c->notifyMove(diffX, diffY);
    }
    ShapeQGraphicsItem::notifyMove(diffX, diffY);
}

/**
 * To Handler which GraphicsItem will be Seelcted
 */
void CompositeQGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QPoint p = event->pos().toPoint();
    int x = p.x() + static_cast<int>(this->x());
    int y = p.y() + static_cast<int>(this->y());
    this->controller->clearSelectd();

    if (isSelected()) {

        for (auto c : childs) {
            c->setSelected(false);
        }

        for (reverse_iterator<vector<ShapeQGraphicsItem *>::iterator> ri = childs.rbegin(); ri != childs.rend(); ri++) {
            if ((*ri)->isCollision(x, y)) {
                if (dynamic_cast<CompositeQGraphicsItem *>(*ri)) {
                    // this item is composite , maybe something in this composite will be selected
                    (*ri)->setSelected(true);
                    (*ri)->_graphics->isSelected = true;
                    if (!this->controller->hasSelectedTarget()) {
                        this->controller->setSelectedTarget((*ri)->_graphics,
                                                            static_cast<CompositeGraphics *>(this->_graphics));
                    }
//                    if (!this->w->hasSelectedTarget()) {
//                        this->w->setSelectedTarget((*ri)->_graphics, static_cast<CompositeGraphics *>(this->_graphics));
//                    }
                } else {
                    // this item is simpleGraphic , and it target

//                    this->w->setSelectedTarget((*ri)->getGraphics(), static_cast<CompositeGraphics *>(this->_graphics));
                    this->controller->setSelectedTarget((*ri)->getGraphics(),
                                                        static_cast<CompositeGraphics *>(this->_graphics));
                    (*ri)->setSelected(true);
                    (*ri)->_graphics->isSelected = true;
                }
                break;
            } else {
                (*ri)->setSelected(false);
            }
        }
//        if(!this->w->hasSelectedTarget()){
//            this->w->setSelectedTarget(this->_graphics, 0);
//        }
        if (!this->controller->hasSelectedTarget()) {
            this->controller->setSelectedTarget(this->_graphics, 0);
        }
    }
//    this->w->updateTreeModel();
    ShapeQGraphicsItem::mouseReleaseEvent(event);
}

bool CompositeQGraphicsItem::isCollision(int x, int y) {
    BoundingBox r = static_cast<SimpleGraphics *>(this->_graphics)->getBoundingBox();
    int llx = r.getX();
    int lly = r.getY();
    int w = r.getWidth();
    int h = r.getHeight();

    for (auto c : childs) {
        c->setSelected(false);
    }

    if (x < llx || x > llx + w || y < lly || y > lly + h) {
        return false;
    }

    for (reverse_iterator<vector<ShapeQGraphicsItem *>::iterator> c = childs.rbegin(); c != childs.rend(); c++) {
        if ((*c)->isCollision(x, y)) {
            (*c)->setSelected(true);
//            this->w->setSelectedTarget((*c)->_graphics, static_cast<CompositeGraphics *>(this->_graphics));
            this->controller->setSelectedTarget((*c)->_graphics, static_cast<CompositeGraphics *>(this->_graphics));
            break;
        }
    }

    return true;
}
