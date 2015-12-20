//
// Created by Raccoon on 2015/12/7.
//

#include "gui/shapegraphicitem/ShapeQGraphicsItem.h"
#include <QGraphicsScene>

/**
 * constructor
 */
ShapeQGraphicsItem::ShapeQGraphicsItem()
        : _x(0), _y(0), _pen(QPen(QColor(0, 0, 0, 255))) {
    setPos(_x, _y);
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);
//    this->setFlag(QGraphicsItem::ItemIgnoresTransformations);
//    this->setFlag(QGraphicsItem::ItemIsMovable);
}

/**
 * Set the draw pen
 */
void ShapeQGraphicsItem::setPen(QPen &pen) {
    this->_pen = pen;
}

/**
 * Paint event
 */
void ShapeQGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    if (!this->scene()) {
        painter->setPen(_pen);
        this->draw(painter);
        return;
    }

    if (isSelected() && !_isDraging) {
        _pen.setStyle(Qt::PenStyle::DashLine);
        painter->setPen(_pen);
        this->draw(painter);
        return;
    }

    if (_isDraging) {
        _pen.setStyle(Qt::DotLine);
        painter->setPen(_pen);
        this->dragDraw(painter);
    } else {
        _pen.setStyle(Qt::SolidLine);
        painter->setPen(_pen);
        this->draw(painter);
    }
}

/**
 * thie item's bounding box
 */
QRectF ShapeQGraphicsItem::boundingRect() const {
    if (_isDraging) {
        return this->dragBoundingbox();
    } else {
        return this->boundingbox();
    }

}

bool ShapeQGraphicsItem::isDragable() const {
    return _dragable;
}

void ShapeQGraphicsItem::setDragable(bool _dragable) {
    this->_dragable = _dragable;
}

using namespace std;

/**
 * below event are provide a mouse drag event
 */
void ShapeQGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
//    cout << "mousePressEvent" << endl;

    if (event->button() == Qt::LeftButton && _dragable) { // only use left button of mouse , can drag grapihcs
        _isDraging = true;
        _dragX = _x;
        _dragY = _y;
        _dragStart = event->pos().toPoint();

        this->scene()->update();
        this->update();
    }
    QGraphicsItem::mousePressEvent(event);
}

void ShapeQGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
//    cout << "mouseMoveEvent" << endl;
    if (_isDraging) {
        QPoint _draging = event->pos().toPoint();

        int diffX = _draging.x() - _dragStart.toPoint().x();
        int diffY = _draging.y() - _dragStart.toPoint().y();
        _dragX = (_x + diffX);
        _dragY = (_y + diffY);

        this->scene()->update();
        this->update();
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void ShapeQGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
//    cout << "mouseReleaseEvent" << endl;
    if (_isDraging) {
        _isDraging = false;
        QPointF _dragEnd = event->pos();
        qreal diffX = _dragEnd.x() - _dragStart.x();
        qreal diffY = _dragEnd.y() - _dragStart.y();

        int diffX_int = static_cast<int>(diffX);
        int diffY_int = static_cast<int>(diffY);

        if (diffX_int == 0 && diffY == 0) return;

        this->w->doCmdMovePre();

        this->_x += diffX_int;
        this->_y += diffY_int;

        QPointF currentPoint = pos();

        this->setPos(pos().x() + _x, pos().y() + _y);
        this->notifyMove(_x, _y);

        this->w->doCmdMove();

        _x = 0;
        _y = 0;
        this->scene()->setSceneRect(this->scene()->itemsBoundingRect());

        this->setSelected(false);

        this->scene()->update();
        this->update();
    }

    QGraphicsItem::mouseReleaseEvent(event);
}

void ShapeQGraphicsItem::setGraphics(Graphics *g) {
    this->_graphics = g;
}

ShapeQGraphicsItem::ShapeQGraphicsItem(Graphics *g)
        : ShapeQGraphicsItem::ShapeQGraphicsItem() {
    this->setGraphics(g);
}

void ShapeQGraphicsItem::notifyMove(int x, int y) {
}

Graphics *ShapeQGraphicsItem::getGraphics() {
    return this->_graphics;
}
