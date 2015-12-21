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

void CompositeQGraphicsItem::notifyMove(int x, int y) {
    if (!this->scene()) {
        _relativeX += x;
        _relativeY += y;
    }
    for (auto c : childs) {
        c->notifyMove(x, y);
    }
}

void CompositeQGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    ShapeQGraphicsItem::mouseReleaseEvent(event);
    cout << "mouseReleaseEvent\n";
    cout << "IsSelected : " << this->isSelected() << "\n";

    QPoint p = event->pos().toPoint();
    int x = p.x() + static_cast<int>(this->x());
    int y = p.y() + static_cast<int>(this->y());

    if (isSelected()) {

        for (auto c : childs) {
            c->setSelected(false);
        }

        for (reverse_iterator<vector<ShapeQGraphicsItem *>::iterator> ri = childs.rbegin(); ri != childs.rend(); ri++) {
            if ((*ri)->isCollision(x, y)) {
                (*ri)->setSelected(true);
                (*ri)->_graphics->isSelected = true;
                break;
            } else {
                (*ri)->setSelected(false);
            }
        }
    }
    this->w->updateTreeModel();
    cout << "Click Point: (" << x << ", " << y << ")\n";
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
            break;
        }
    }

//    for (auto c : childs) {
//        if (c->isCollision(x, y)) {
//            c->setSelected(true);
//            break;
//        }
//    }


    return true;
}
