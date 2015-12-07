#include "DrawingArea.h"

DrawingArea::DrawingArea() {

    layout = new QVBoxLayout(0);
    view = new QGraphicsView;
    scene = new QGraphicsScene(0);

    layout->addWidget(view);
    layout->setMargin(0);
    view->setScene(scene);

    this->setLayout(layout);
}

DrawingArea::~DrawingArea() {
    delete layout;
    delete view;
    delete scene;
}

QGraphicsScene *DrawingArea::getScene() {
    return scene;
}
QGraphicsView *DrawingArea::getView()
{
    return view;
}
