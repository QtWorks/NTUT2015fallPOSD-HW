//
// Created by Raccoon on 2015/11/22.
//

#ifndef DRAWING_AREA_H
#define DRAWING_AREA_H

#include <QWidget>
#include <QBoxLayout>
#include <QGraphicsView>
#include <QTreeView>

class DrawingArea : public QWidget {
Q_OBJECT

public:
    DrawingArea();
    virtual ~DrawingArea();

    QGraphicsScene *getScene();
    QTreeView *getTreeView();
    QGraphicsView *getView();

protected:
private:
    QBoxLayout *layout;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QTreeView *treeView;

private slots:

};


#endif //INC_104598003_HW4_DRAWINGAREA_H
