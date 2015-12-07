//
// Created by Raccoon on 2015/11/22.
//

#ifndef DRAWING_AREA_H
#define DRAWING_AREA_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGraphicsView>

class DrawingArea : public QWidget {
    Q_OBJECT
public:
    DrawingArea();
    virtual ~DrawingArea();

    QGraphicsScene * getScene();
    QGraphicsView *getView();

protected:
private:
    QVBoxLayout *layout;
    QGraphicsView *view;
    QGraphicsScene *scene;
private slots:
};


#endif //INC_104598003_HW4_DRAWINGAREA_H
