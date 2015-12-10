//
// Created by Raccoon on 2015/12/11.
//

#include "CoordinateAxisGraphicsItem.h"

#include <sstream>

#include <QGraphicsScene>
#include <QPainter>

using namespace std;

void CoordinateAxisGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    QFont f = painter->font();
    f.setPointSize(f.pointSize()*1.5);
    painter->setFont(f);

    QRectF b = boundingRect();
    QRect b2 = b.toRect();

    painter->drawLine(b2.x(), 0, b2.x() + b2.width(), 0);
    painter->drawLine(0, b2.y(), 0, b2.y() + b2.height());
    painter->drawLine(b2.x() + b2.width(), 0, b2.x() + b2.width() - 10, -10);
    painter->drawLine(b2.x() + b2.width(), 0, b2.x() + b2.width() - 10, 10);
    painter->drawLine(0, b2.y() + b2.height(), 10, b2.y() + b2.height() - 10);
    painter->drawLine(0, b2.y() + b2.height(), -10, b2.y() + b2.height() - 10);

    int dim = 50;
    for (int i = b2.x() + dim; i < b2.x() + b2.width(); i += dim) {
        painter->drawLine(i, -10, i, 10);
    }
    for (int i = b2.y() + dim; i < b2.y() + b2.height(); i += dim) {
        painter->drawLine(-10, i, 10, i);
    }
}

QRectF CoordinateAxisGraphicsItem::boundingRect() const {
    qreal widget = this->scene()->width();
    qreal height = this->scene()->height();
    qreal x = this->scene()->sceneRect().x();
    qreal y = this->scene()->sceneRect().y();
    return QRectF(x, y, widget, height);
}
