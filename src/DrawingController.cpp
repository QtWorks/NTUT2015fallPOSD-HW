//
// Created by Raccoon on 2016/1/4.
//

#include "DrawingController.h"
#include "GraphicsModel.h"
#include "CommandManager.h"
#include "CoordinateAxisGraphicsItem.h"
#include "QtGraphicsViewVisitor.h"
#include "QtGraphicsToStandardItemModelVisitor.h"
#include "View.h"


#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

#include <iostream>
#include <string>
using namespace std;

DrawingController::DrawingController() {
    _model = new GraphicsModel();
    _commandManager = new CommandManager(this, this->_model);
    initializeView();
}

void DrawingController::initializeView() {
    setWindowTitle("POSD Homework#7");
    this->resize(1024, 768);


    this->initializeAction();
    this->setConnect();

    this->createMenuBar();
    this->attachMenuAction();

    this->createToolMenuBar();
    this->attachToolMenuAction();

    this->createCentralWidget();
    this->setCentralWidget(centralWidget);

    this->updateScene();
    this->updateActionState();
}

DrawingController::~DrawingController() {

}

/**
 * Create View Method
 */

void DrawingController::initializeAction() {
    loadFileAction = new QAction(QIcon("./icon/open_2.png"), "loadFile", this);
    saveFileAction = new QAction(QIcon("./icon/save_2.png"), "saveFile", this);

    aboutDeveloperAction = new QAction("aboutDeveloper", this);

    createSquareAction = new QAction(QIcon("./icon/square.png"), "createSquare", this);
    createRectangleAction = new QAction(QIcon("./icon/rectangle.png"), "createRectangle", this);
    createCircleAction = new QAction(QIcon("./icon/circle.png"), "createCircle", this);

    groupAction = new QAction(QIcon("./icon/group.png"), "group", this);
    ungroupAction = new QAction(QIcon("./icon/ungroup.png"), "ungroup", this);

    deleteSimpleGraphicAction = new QAction(QIcon("./icon/delete.png"), "delete", this);

    redoAction = new QAction(QIcon("./icon/redo.png"), "redo", this);
    undoAction = new QAction(QIcon("./icon/undo.png"), "undo", this);

    upperLayerAction = new QAction(QIcon("./icon/upperlayer.png"), "upper layer", this);
    lowerLayerAction = new QAction(QIcon("./icon/lowerlayer.png"), "lower layer", this);
}

void DrawingController::setConnect() {
    connect(loadFileAction, SIGNAL(triggered(bool)), this, SLOT(doOpenFile()));
    connect(saveFileAction, SIGNAL(triggered(bool)), this, SLOT(doSaveFile()));

    connect(redoAction, SIGNAL(triggered(bool)), this, SLOT(doRedo()));
    connect(undoAction, SIGNAL(triggered(bool)), this, SLOT(doUndo()));

    connect(createSquareAction, SIGNAL(triggered(bool)), this, SLOT(doCreateSquare()));
    connect(createCircleAction, SIGNAL(triggered(bool)), this, SLOT(doCreateCircle()));
    connect(createRectangleAction, SIGNAL(triggered(bool)), this, SLOT(doCreateRectangle()));

    connect(deleteSimpleGraphicAction, SIGNAL(triggered(bool)), this, SLOT(doDeleteSimpleGraphics()));

    connect(groupAction, SIGNAL(triggered(bool)), this, SLOT(doGroup()));
    connect(ungroupAction, SIGNAL(triggered(bool)), this, SLOT(doUnGroup()));

    connect(upperLayerAction, SIGNAL(triggered(bool)), this, SLOT(doUpperLayer()));
    connect(lowerLayerAction, SIGNAL(triggered(bool)), this, SLOT(doLowerLayer()));

    connect(aboutDeveloperAction, SIGNAL(triggered(bool)), this, SLOT(doAboutDeveloper()));
}

void DrawingController::createMenuBar() {
    fileMenu = this->menuBar()->addMenu("File");
    aboutMenu = this->menuBar()->addMenu("About");
    createShapeMenu = this->menuBar()->addMenu("Create Shape");
}

void DrawingController::attachMenuAction() {
    fileMenu->addAction(loadFileAction);
    fileMenu->addAction(saveFileAction);

    aboutMenu->addAction(aboutDeveloperAction);

    createShapeMenu->addAction(createSquareAction);
    createShapeMenu->addAction(createRectangleAction);
    createShapeMenu->addAction(createCircleAction);
}

void DrawingController::createToolMenuBar() {
    toolMenuBar = new QToolBar();
    this->addToolBar(toolMenuBar);
}

void DrawingController::attachToolMenuAction() {
    toolMenuBar->addAction(loadFileAction);
    toolMenuBar->addAction(saveFileAction);

    toolMenuBar->addSeparator();
    toolMenuBar->addAction(undoAction);
    toolMenuBar->addAction(redoAction);

    toolMenuBar->addSeparator();
    toolMenuBar->addAction(createCircleAction);
    toolMenuBar->addAction(createRectangleAction);
    toolMenuBar->addAction(createSquareAction);

    toolMenuBar->addSeparator();
    toolMenuBar->addAction(deleteSimpleGraphicAction);

    toolMenuBar->addSeparator();
    toolMenuBar->addAction(groupAction);
    toolMenuBar->addAction(ungroupAction);

    toolMenuBar->addSeparator();
    toolMenuBar->addAction(upperLayerAction);
    toolMenuBar->addAction(lowerLayerAction);

    toolMenuBar->addSeparator();
}

void DrawingController::createCentralWidget() {

    centralWidget = new QSplitter(Qt::Horizontal);
    treeView = new QTreeView(0);


    view = new View(this);
    scene = new QGraphicsScene(0);

    view->setScene(scene);
    view->setDragMode(QGraphicsView::DragMode::RubberBandDrag);
    view->setRubberBandSelectionMode(Qt::ItemSelectionMode::ContainsItemBoundingRect);
    view->scale(1, -1);

    scene->setSceneRect(-400, -300, 800, 600);

    treeView->setHeaderHidden(true);
    treeView->setWordWrap(true);
    treeView->setEditTriggers(0);
    treeView->setExpandsOnDoubleClick(false);
    treeView->setItemsExpandable(false);

    centralWidget->setContentsMargins(10, 10, 10, 10);
    centralWidget->addWidget(treeView);
    centralWidget->addWidget(view);
}

/**
 * View Action
 */

void DrawingController::doOpenFile() {
    if (isDirty) {
        QMessageBox::StandardButton requireCheck;
        requireCheck = QMessageBox::question(this, "Drawing",
                                             "This graph has been changed, but without saved.\n do you want to load other files?",
                                             QMessageBox::Yes | QMessageBox::No);
        if (requireCheck == QMessageBox::No) {
            return;
        }
    }
    QString filename;
    QString currentPath = getCurrentPath();

    filename = QFileDialog::getOpenFileName(this, "Choose Graphics File", currentPath, "Graphics Files (*.txt)");

    if (filename == "") {
        showWarningDialog("Not Selected any file");
        return;
    }
    _model->loadFromFile(filename.toUtf8().constData());
    _commandManager->clear();
    isDirty = false;
    this->updateScene();
    this->updateActionState();
}

void DrawingController::doSaveFile() {
    QString filename;
    QString currentPath = getCurrentPath();

    filename = QFileDialog::getSaveFileName(this, "Choose Save Path and Name", currentPath, "Graphics Files (*.txt)");

    if (filename == "") {
        showWarningDialog("not specific any filename");
        return;
    }
    _model->saveToFile(filename.toUtf8().constData());
}

void DrawingController::doUndo() {
    _commandManager->undo();
    this->updateScene();
    this->updateActionState();
}

void DrawingController::doRedo() {
    _commandManager->redo();
    this->updateScene();
    this->updateActionState();
}

void DrawingController::doCreateSquare() {
    isDirty = true;
    _commandManager->createSquare();
    this->updateScene();
    this->updateActionState();
}

void DrawingController::doCreateCircle() {
    isDirty = true;
    _commandManager->createCircle();
    this->updateScene();
    this->updateActionState();
}

void DrawingController::doCreateRectangle() {
    isDirty = true;
    _commandManager->createRectangle();
    this->updateScene();
    this->updateActionState();
}

void DrawingController::doDeleteSimpleGraphics() {
    isDirty = true;
    _commandManager->deleteSimpleGraphic();
    this->updateScene();
    this->updateActionState();
}

void DrawingController::doGroup() {
    isDirty = true;
    _commandManager->group();
    this->updateScene();
    this->updateActionState();
}

void DrawingController::doUnGroup() {
    isDirty = true;
    _commandManager->ungroup();
    this->updateScene();
    this->updateActionState();
}

void DrawingController::doUpperLayer() {
    isDirty = true;
    _commandManager->upperLayer();
    this->updateScene();
    this->updateActionState();
}

void DrawingController::doLowerLayer() {
    isDirty = true;
    _commandManager->lowerLayer();
    this->updateScene();
    this->updateActionState();
}

void DrawingController::doAboutDeveloper() {
    QMessageBox aboutDeveloperMessageBox;
    aboutDeveloperMessageBox.setWindowTitle("About");
    aboutDeveloperMessageBox.setText("104598003\nAuthor:李柏鋐");
    aboutDeveloperMessageBox.exec();
}

void DrawingController::updateActionState() {
    this->undoAction->setEnabled(_commandManager->canUndo());
    this->redoAction->setEnabled(_commandManager->canRedo());

    this->groupAction->setEnabled(this->canGroup());
    this->ungroupAction->setEnabled(this->canUngroup());

    this->upperLayerAction->setEnabled(this->canUpperLayer());
    this->lowerLayerAction->setEnabled(this->canLowerLayer());

    this->deleteSimpleGraphicAction->setEnabled(this->canDelete());
}

/**
 * Helper Function
 */

QString DrawingController::getCurrentPath() {
    return QDir::currentPath();
}

void DrawingController::showWarningDialog(string message) {
    QMessageBox::warning(0, "Warning", QString(message.c_str()));
}

void DrawingController::updateScene() {
    scene->clear();
    scene->addItem(new CoordinateAxisGraphicsItem);
    QtGraphicsViewVisitor *visitor = new QtGraphicsViewVisitor(this->scene);
    visitor->controller = this;
    _model->getModel()->accept(*visitor);
    visitor->draw();
    view->update();

    QtGraphicsToStandardItemModelVisitor *modelVisitor = new QtGraphicsToStandardItemModelVisitor;
    _model->getModel()->accept(*modelVisitor);
    treeView->setModel(0);
    treeView->setModel(modelVisitor->getModel());
    treeView->expandAll();
}

void DrawingController::onItemSelected() {
    cout << "View Event : itemSelected" << endl;
    this->clearSelectd();
    this->updateActionState();
}

bool DrawingController::canGroup() {
    return this->scene->selectedItems().count() >= 2;
}

bool DrawingController::canUngroup() {
    return this->scene->selectedItems().count() == 1 &&
           dynamic_cast<CompositeQGraphicsItem *>(this->scene->selectedItems().first());

}

QList<QGraphicsItem *> DrawingController::getGraphicsItems() {
    return this->scene->items();
}


void DrawingController::setSelectedTarget(Graphics *target, CompositeGraphics *parentContainer) {
    cout << "test" << endl;
    this->selectedTarget = target;
    this->selectedParent = parentContainer;
    if (!parentContainer) {
        this->selectedParent = this->_model->getModel();
    }
    this->updateActionState();
}

void DrawingController::clearSelectd() {
    this->selectedParent = 0;
    this->selectedTarget = 0;
    this->updateActionState();
}

bool DrawingController::hasSelectedTarget() {
    return (bool) selectedTarget;
}

bool DrawingController::canUpperLayer() {
    return (this->selectedTarget && this->selectedParent &&
            (*this->selectedParent->_graphics.begin()) != selectedTarget);
}

bool DrawingController::canLowerLayer() {
    return (this->selectedTarget && this->selectedParent &&
            (*this->selectedParent->_graphics.rbegin()) != selectedTarget);
}

Graphics *DrawingController::getSelectedTarget() {
    return selectedTarget;
}

CompositeGraphics *DrawingController::getSelectedParent() {
    return selectedParent;
}

bool DrawingController::canDelete() {
    return this->scene->selectedItems().count() == 1 && this->selectedParent == this->_model->getModel();
}

void DrawingController::onItemMove(ShapeQGraphicsItem *item, int diffX, int diffY) {
    this->_commandManager->move(item, diffX, diffY);
    this->updateScene();
    this->updateActionState();
}
