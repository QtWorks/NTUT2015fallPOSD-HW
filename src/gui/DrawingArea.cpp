#include "DrawingArea.h"
#include <QTreeView>
#include <QHBoxLayout>
#include <QSplitter>

DrawingArea::DrawingArea() {

    layout = new QHBoxLayout(0);

    // use Splitter to enable user use mouse to adjust size
    QSplitter *splitter = new QSplitter;

    view = new QGraphicsView;
    scene = new QGraphicsScene(0);
    treeView = new QTreeView(0);
    treeView->setHeaderHidden(true);
    treeView->setWordWrap(true);
    treeView->setEditTriggers(0);
    treeView->setExpandsOnDoubleClick(false);
    treeView->setItemsExpandable(false);

    splitter->addWidget(treeView);
    splitter->addWidget(view);

    layout->addWidget(splitter);
//    layout->setMargin(3);


    view->setScene(scene);

    view->setDragMode(QGraphicsView::DragMode::RubberBandDrag);
    view->setRubberBandSelectionMode(Qt::ItemSelectionMode::ContainsItemBoundingRect);
    view->scale(1, -1);

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

QGraphicsView *DrawingArea::getView() {
    return view;
}

QTreeView * DrawingArea::getTreeView(){
    return treeView;
}
