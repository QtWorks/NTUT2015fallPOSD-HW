#include "DrawingWindow.h"

#include <fstream>

#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QtWidgets/qtoolbutton.h>
#include "gui/shapegraphicitem/ShapeQGraphicsItem.h"

#include "gui/CoordinateAxisGraphicsItem.h"

#include "QtGraphicsViewVisitor.h"
#include "DescriptionVisitor.h"
#include "GraphicsFactory.h"
#include "MultiRootGraphicFactory.h"

#include "compositegraphics.h"
#include "RootGraphics.h"
#include "simplegraphics.h"
#include "compositegraphics.h"

#include "Command.h"
#include "CreateCircleCmd.h"
#include "CreateRectangleCmd.h"
#include "CreateSquareCmd.h"
#include "GroupCmd.h"
#include "UnGroupCmd.h"
#include "DeleteCmd.h"
#include "MoveCmd.h"

using namespace std;

DrawingWindow::DrawingWindow() {
    this->setWindowTitle("POSD Homework#5");
    this->resize(800, 600);

    this->activateGraphics = new RootGraphics();

    createMenuBar();
    createToolMenuBar();
    createGraphicsView();

    this->loadFile("00.txt");
}

DrawingWindow::~DrawingWindow() {

}

void DrawingWindow::createMenuBar() {
    fileMenu = this->menuBar()->addMenu("File");
    aboutMenu = this->menuBar()->addMenu("About");
    createShapeMenu = this->menuBar()->addMenu("Create Shape");
    initializeMenuAction();
}

void DrawingWindow::initializeMenuAction() {
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

    redoAction->setEnabled(false);
    undoAction->setEnabled(false);

    setConnect();
    AttachAction();
}

void DrawingWindow::setConnect() {
    connect(aboutDeveloperAction, SIGNAL(triggered(bool)), this, SLOT(doAboutDeveloper()));
    connect(loadFileAction, SIGNAL(triggered(bool)), this, SLOT(doOpenFile()));
    connect(saveFileAction, SIGNAL(triggered(bool)), this, SLOT(doSaveFile()));

    connect(createSquareAction, SIGNAL(triggered(bool)), this, SLOT(doCmdCreateSquare()));
    connect(createCircleAction, SIGNAL(triggered(bool)), this, SLOT(doCmdCreateCircle()));
    connect(createRectangleAction, SIGNAL(triggered(bool)), this, SLOT(doCmdCreateRectangle()));

    connect(groupAction, SIGNAL(triggered(bool)), this, SLOT(doCmdGroup()));
    connect(ungroupAction, SIGNAL(triggered(bool)), this, SLOT(doCmdUnGroup()));

    connect(deleteSimpleGraphicAction, SIGNAL(triggered(bool)), this, SLOT(doCmdDeleteSimpleGraphics()));

    connect(redoAction, SIGNAL(triggered(bool)), this, SLOT(doRedo()));
    connect(undoAction, SIGNAL(triggered(bool)), this, SLOT(doUndo()));
}

void DrawingWindow::AttachAction() const {
    fileMenu->addAction(loadFileAction);
    fileMenu->addAction(saveFileAction);

    aboutMenu->addAction(aboutDeveloperAction);

    createShapeMenu->addAction(createSquareAction);
    createShapeMenu->addAction(createRectangleAction);
    createShapeMenu->addAction(createCircleAction);
}

void DrawingWindow::createGraphicsView() {
    mainWidget = new DrawingArea();
    this->setCentralWidget(mainWidget);
    mainWidget->getScene()->setSceneRect(-400, -300, 800, 600);
    mainWidget->getScene()->addItem(new CoordinateAxisGraphicsItem);
}

void DrawingWindow::resizeScene() const {
    QRectF p = mainWidget->getScene()->itemsBoundingRect();
    int x = p.center().toPoint().x();
    int y = p.center().toPoint().y();

    int widgetX = static_cast<int>(mainWidget->getScene()->itemsBoundingRect().width()) + 200;
    int widgetY = static_cast<int>(mainWidget->getScene()->itemsBoundingRect().height()) + 200;

    if (widgetX < 800) widgetX = 800;
    if (widgetY < 600) widgetY = 600;

    mainWidget->getScene()->setSceneRect(x - widgetX / 2, y - widgetY / 2, widgetX, widgetY);
}

void DrawingWindow::createToolMenuBar() {
    toolMenuBar = new QToolBar();
    toolMenuBar->addAction(loadFileAction);
    toolMenuBar->addAction(saveFileAction);

    toolMenuBar->addSeparator();

    toolMenuBar->addAction(createCircleAction);
    toolMenuBar->addAction(createRectangleAction);
    toolMenuBar->addAction(createSquareAction);

    toolMenuBar->addSeparator();

    toolMenuBar->addAction(groupAction);
    toolMenuBar->addAction(ungroupAction);

    toolMenuBar->addSeparator();

    toolMenuBar->addAction(undoAction);
    toolMenuBar->addAction(redoAction);

    toolMenuBar->addSeparator();

    toolMenuBar->addAction(deleteSimpleGraphicAction);

    toolMenuBar->addSeparator();

    this->addToolBar(toolMenuBar);
}

void DrawingWindow::doAboutDeveloper() {
    QMessageBox aboutDeveloperMessageBox;
    aboutDeveloperMessageBox.setWindowTitle("About");
    aboutDeveloperMessageBox.setText("104598003\nAuthor:李柏鋐");
    aboutDeveloperMessageBox.exec();
}

void DrawingWindow::doOpenFile() {
    QString filename;
    QString currentPath = getCurrentPath();

    filename = QFileDialog::getOpenFileName(this, "Choose Graphics File", currentPath, "Graphics Files (*.txt)");

    if (filename == "") {
        showWarningDialog("Not Selected any file");
        return;
    }
    loadFile(filename.toUtf8().constData());
}

QString DrawingWindow::getCurrentPath() {
    return QDir::currentPath();
}

void DrawingWindow::doSaveFile() {
    if (activateGraphics) {
        DescriptionVisitor *visitor = new DescriptionVisitor;
        activateGraphics->accept(*visitor);
        string saveContents = visitor->getDescription();
        QString currentPath = getCurrentPath();
        QString filename;

        filename = QFileDialog::getSaveFileName(this, "Choose Save Path and Name", currentPath,
                                                "Graphics Files (*.txt)");

        if (filename == "") {
            showWarningDialog("not specific any filename");
            return;
        }

        ofstream ofs;
        ofs.open(filename.toUtf8().constData());
        ofs << saveContents;
        ofs.close();
    } else {
        showWarningDialog("There hasn't any graphics!");
    }
}

void DrawingWindow::loadFile(std::string filename) {
    GraphicsFactory *graphicsFactory = new MultiRootGraphicFactory;
    try {
        Graphics *graphics = graphicsFactory->buildGraphicsFromFile(filename.c_str());
        this->activateGraphics = graphics;
    }
    catch (std::string e) {
        cout << e << endl;
        showWarningDialog(e);
        return;
    }
    updateScene();
}

void DrawingWindow::updateScene() {
    mainWidget->getScene()->clear();
    resizeScene();
    mainWidget->getScene()->addItem(new CoordinateAxisGraphicsItem);
    QtGraphicsViewVisitor *visitor = new QtGraphicsViewVisitor(mainWidget->getScene());
    visitor->w = this;
    activateGraphics->accept(*visitor);
    visitor->draw();
    mainWidget->getScene()->update();
    resizeScene();
}

void DrawingWindow::showWarningDialog(string message) {
    QMessageBox::warning(0, "Warning", QString(message.c_str()));
}

void DrawingWindow::doCreateSquare() {
    Shape *square = new Square(0, 0, 100);
    this->activateGraphics->add(new SimpleGraphics(square));
    updateScene();
}


void DrawingWindow::doCreateCircle() {
    Shape *square = new Circle(0, 0, 50);
    this->activateGraphics->add(new SimpleGraphics(square));
    updateScene();
}

void DrawingWindow::doCreateRectangle() {
    Shape *square = new Rectangle(0, 0, 300, 150);
    this->activateGraphics->add(new SimpleGraphics(square));
    updateScene();
}

void DrawingWindow::doGroup() {

    CompositeGraphics *cg = new CompositeGraphics;

    for (auto e : mainWidget->getScene()->selectedItems()) {
        cg->add(static_cast<ShapeQGraphicsItem *>(e)->getGraphics());
        static_cast<RootGraphics *>(this->activateGraphics)->remove(
                static_cast<ShapeQGraphicsItem *>(e)->getGraphics());
    }
    this->activateGraphics->add(cg);
    this->updateScene();
}

void DrawingWindow::doUnGroup() {
    for (auto e : mainWidget->getScene()->selectedItems()) {

        CompositeGraphics *cg = static_cast<CompositeGraphics *>(static_cast<CompositeQGraphicsItem *>(e)->getGraphics());
        if (cg) {
            for (auto gs : cg->_graphics) {
                this->activateGraphics->add(gs);
            }
            static_cast<RootGraphics *>(this->activateGraphics)->remove(
                    static_cast<ShapeQGraphicsItem *>(e)->getGraphics());
        }
    }
    this->updateScene();
}

void DrawingWindow::doDeleteSimpleGraphics() {
    for (auto e : mainWidget->getScene()->selectedItems()) {
        static_cast<RootGraphics *>(this->activateGraphics)->remove(
                static_cast<ShapeQGraphicsItem *>(e)->getGraphics());
    }
    this->updateScene();
}


void DrawingWindow::doUndo() {
    if (!this->command_undoCmds.empty()) {
        Command *c = this->command_undoCmds.top();
        this->command_undoCmds.pop();
        c->unexecute();
        this->command_redoCmds.push(c);
        if (this->command_undoCmds.empty()) {
            this->undoAction->setEnabled(false);
        }

        this->redoAction->setEnabled(true);
    }
}

void DrawingWindow::doRedo() {
    cout << "Command - Redo -size " << command_redoCmds.size() << endl;
    if (this->command_redoCmds.size() > 0) {
        Command *c = this->command_redoCmds.top();
        this->command_redoCmds.pop();
        this->undoAction->setEnabled(true);
        c->execute();
        this->command_undoCmds.push(c);
        if (this->command_redoCmds.empty()) {
            this->redoAction->setEnabled(false);
        }
    }

}


/**
 * Command action of  Command Pattern
 */

void DrawingWindow::doCmdCreateSquare() {
    Command *c = new CreateSquareCmd(this);
    this->command_undoCmds.push(c);
    this->undoAction->setEnabled(true);
    this->redoAction->setEnabled(false);
    c->execute();
    this->clearRedoStack();
}

void DrawingWindow::doCmdCreateCircle() {
    Command *c = new CreateCircleCmd(this);
    this->command_undoCmds.push(c);
    this->undoAction->setEnabled(true);
    this->redoAction->setEnabled(false);
    c->execute();
    this->clearRedoStack();
}

void DrawingWindow::doCmdCreateRectangle() {
    Command *c = new CreateRectangleCmd(this);
    this->command_undoCmds.push(c);
    this->undoAction->setEnabled(true);
    this->redoAction->setEnabled(false);
    c->execute();
    this->clearRedoStack();
}

void DrawingWindow::doCmdGroup() {
    Command *c = new GroupCmd(this);
    this->command_undoCmds.push(c);
    this->undoAction->setEnabled(true);
    this->redoAction->setEnabled(false);
    c->execute();
    this->clearRedoStack();
}

void DrawingWindow::doCmdUnGroup() {
    Command *c = new UnGroupCmd(this);
    this->command_undoCmds.push(c);
    this->undoAction->setEnabled(true);
    this->redoAction->setEnabled(false);
    c->execute();
    this->clearRedoStack();
}

void DrawingWindow::doCmdDeleteSimpleGraphics() {
    Command *c = new DeleteCmd(this);
    this->command_undoCmds.push(c);
    this->undoAction->setEnabled(true);
    this->redoAction->setEnabled(false);
    c->execute();
    this->clearRedoStack();
}

void DrawingWindow::clearRedoStack() {
    while (!this->command_redoCmds.empty()) {
        this->command_redoCmds.pop();
    }
}

void DrawingWindow::doCmdMove() {
    DescriptionVisitor v;
    this->activateGraphics->accept(v);
    static_cast<MoveCmd *>(this->command_undoCmds.top())->checkpoint2 = v.getDescription();
    this->undoAction->setEnabled(true);
    this->redoAction->setEnabled(false);
    this->clearRedoStack();
}

void DrawingWindow::doCmdMovePre() {
    this->command_undoCmds.push(new MoveCmd(this));
    DescriptionVisitor v;
    this->activateGraphics->accept(v);
    static_cast<Command *>(this->command_undoCmds.top())->checkpoint = v.getDescription();
}
