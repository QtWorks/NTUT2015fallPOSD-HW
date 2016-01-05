//
// Created by Raccoon on 2016/1/5.
//

#ifndef POSD_104598003_HW7_VIEW_H
#define POSD_104598003_HW7_VIEW_H

#include <QGraphicsView>

class DrawingController;

class View : public QGraphicsView {
Q_OBJECT
public:
    View(DrawingController *ctrl);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    DrawingController *controller;
};


#endif //POSD_104598003_HW7_VIEW_H
