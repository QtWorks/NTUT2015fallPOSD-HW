//
// Created by Raccoon on 2015/12/11.
//

#ifndef POSD_104598003_HW5_COORDINATEAXISGRAPHICSITEM_H
#define POSD_104598003_HW5_COORDINATEAXISGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QFont>

class CoordinateAxisGraphicsItem : public QGraphicsItem {

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QFont font;
};


#endif //POSD_104598003_HW5_COORDINATEAXISGRAPHICSITEM_H
