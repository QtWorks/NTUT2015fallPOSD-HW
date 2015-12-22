#include "DrawingWindow.h"

#include <fstream>
#include <utility>

#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QToolButton>
#include "QtGraphicsToStandardItemModelVisitor.h"
#include "gui/shapegraphicitem/ShapeQGraphicsItem.h"

#include "gui/CoordinateAxisGraphicsItem.h"

#include "QtGraphicsViewVisitor.h"
#include "GraphicsFactory.h"
#include "MultiRootGraphicFactory.h"

#include "RootGraphics.h"
#include "simplegraphics.h"

#include "MoveCmd.h"
#include "UpperLayerCmd.h"
#include "LowerLayerCmd.h"

using namespace std;

DrawingWindow::DrawingWindow() {
    this->setWindowTitle("POSD Homework#5");
    this->resize(800, 600);

    this->activateGraphics = new RootGraphics();

    createMenuBar();
    createToolMenuBar();
    createGraphicsView();
}

DrawingWindow::~DrawingWindow() {

}

// -------------------------------------------------------------------------------------------------------------------
/**
 * Set up GUI
 */

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

    upperLayerAction = new QAction(QIcon("./icon/upperlayer.png"), "upper layer", this);
    lowerLayerAction = new QAction(QIcon("./icon/lowerlayer.png"), "lower layer", this);

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

    connect(upperLayerAction, SIGNAL(triggered(bool)), this, SLOT(doCmdUpperLayer()));
    connect(lowerLayerAction, SIGNAL(triggered(bool)), this, SLOT(doCmdLowerLayer()));
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

    toolMenuBar->addAction(upperLayerAction);
    toolMenuBar->addAction(lowerLayerAction);

    toolMenuBar->addSeparator();

    toolMenuBar->addAction(deleteSimpleGraphicAction);

    toolMenuBar->addSeparator();

    this->addToolBar(toolMenuBar);
}

// -------------------------------------------------------------------------------------------------------------------


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
    updateTreeModel();
}

void DrawingWindow::updateTreeModel() {
    QtGraphicsToStandardItemModelVisitor *modelVisitor = new QtGraphicsToStandardItemModelVisitor;
    activateGraphics->accept(*modelVisitor);
    mainWidget->getTreeView()->setModel(0);
    mainWidget->getTreeView()->setModel(modelVisitor->getModel());
    mainWidget->getTreeView()->expandAll();
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
    this->updateTreeModel();
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

    for (auto e : mainWidget->getScene()->items()) {
        if (e->isSelected()) {
            cg->add(static_cast<ShapeQGraphicsItem *>(e)->getGraphics());
            static_cast<RootGraphics *>(this->activateGraphics)->remove(
                    static_cast<ShapeQGraphicsItem *>(e)->getGraphics());
        }
    }

    this->activateGraphics->add(cg);
    this->updateScene();
}

void DrawingWindow::doUnGroup() {
    for (auto e : mainWidget->getScene()->selectedItems()) {

        if (!dynamic_cast<CompositeQGraphicsItem *>(e))return;

        CompositeGraphics *cg =
                dynamic_cast<CompositeGraphics *>(static_cast<CompositeQGraphicsItem *>(e)->getGraphics());
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

void DrawingWindow::doUpperLayer() {
    if (selectedTarget && !selectedParent) {
        selectedParent = static_cast<CompositeGraphics *>(activateGraphics);
    }
    if (hasSelectedTarget()) {
        vector<Graphics *>::iterator pre = selectedParent->_graphics.begin();
        vector<Graphics *>::iterator target = selectedParent->_graphics.begin();

        for (auto child = selectedParent->_graphics.begin();
             child != selectedParent->_graphics.end(); ++child) {
            if ((*child) == selectedTarget) {
                target = child;
                break;
            }
            pre = child;
        }
        if (pre != target) {
            iter_swap(pre, target);
            this->clearSelectd();
            this->updateScene();
        }
    }
}

void DrawingWindow::doLowerLayer() {
    if (hasSelectedTarget()) {
        reverse_iterator<vector<Graphics *>::iterator> pre = selectedParent->_graphics.rbegin();
        reverse_iterator<vector<Graphics *>::iterator> target = selectedParent->_graphics.rbegin();

        for (reverse_iterator<vector<Graphics *>::iterator> child = selectedParent->_graphics.rbegin();
             child != selectedParent->_graphics.rend(); ++child) {
            if ((*child) == selectedTarget) {
                target = child;
                break;
            }
            pre = child;
        }
        if (pre != target) {
            iter_swap(pre, target);
            this->clearSelectd();
            this->updateScene();
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

void DrawingWindow::doCmdUpperLayer() {
    if(this->hasSelectedTarget()){
        Command *c = new UpperLayerCmd(this);
        this->command_undoCmds.push(c);
        this->undoAction->setEnabled(true);
        this->redoAction->setEnabled(false);
        c->execute();
        this->clearRedoStack();
    }
}

void DrawingWindow::doCmdLowerLayer() {
    if(this->hasSelectedTarget()){
        Command *c = new LowerLayerCmd(this);
        this->command_undoCmds.push(c);
        this->undoAction->setEnabled(true);
        this->redoAction->setEnabled(false);
        c->execute();
        this->clearRedoStack();
    }
}

void DrawingWindow::setSelectedTarget(Graphics *target, CompositeGraphics *parentContainer) {
    this->selectedTarget = target;
    this->selectedParent = parentContainer;
    if (!parentContainer) {
        this->selectedParent = static_cast<CompositeGraphics *>(activateGraphics);
    }
}

void DrawingWindow::clearSelectd() {
    this->selectedParent = 0;
    this->selectedTarget = 0;
}

bool DrawingWindow::hasSelectedTarget() {
    return (bool) selectedTarget;
}


