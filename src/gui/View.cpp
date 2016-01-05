//
// Created by Raccoon on 2016/1/5.
//

#include "View.h"
#include "DrawingController.h"

void View::mouseReleaseEvent(QMouseEvent *event) {
    this->controller->onItemSelected();
    QGraphicsView::mouseReleaseEvent(event);
}

View::View(DrawingController *ctrl) {
    this->controller = ctrl;
}
