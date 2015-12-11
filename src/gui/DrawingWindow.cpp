#include "DrawingWindow.h"

#include <fstream>

#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QtWidgets/qtoolbutton.h>

#include "gui/CoordinateAxisGraphicsItem.h"

#include "QtGraphicsViewVisitor.h"
#include "DescriptionVisitor.h"
#include "GraphicsFactory.h"
#include "MultiRootGraphicFactory.h"

#include "compositegraphics.h"
#include "simplegraphics.h"

using namespace std;

DrawingWindow::DrawingWindow() {
    this->setWindowTitle("POSD Homework#5");
    this->resize(800, 600);

    this->activateGraphics = new CompositeGraphics();

    createMenuBar();
    createToolMenuBar();
    createGraphicsView();
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
    loadFileAction = new QAction(QIcon("./icon/Open.png"), "loadFile", this);
    saveFileAction = new QAction(QIcon("./icon/Save.png"), "saveFile", this);
    aboutDeveloperAction = new QAction("aboutDeveloper", this);

    createSquareAction = new QAction("createSquare", this);
    createRectangleAction = new QAction("createRectangle", this);
    createCircleAction = new QAction("createCircle", this);

    setConnect();
    AttachAction();
}

void DrawingWindow::setConnect() {
    connect(aboutDeveloperAction, SIGNAL(triggered(bool)), this, SLOT(doAboutDeveloper()));
    connect(loadFileAction, SIGNAL(triggered(bool)), this, SLOT(doOpenFile()));
    connect(saveFileAction, SIGNAL(triggered(bool)), this, SLOT(doSaveFile()));
    connect(createSquareAction, SIGNAL(triggered(bool)), this, SLOT(doCreateSquare()));
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

    int widgetX = mainWidget->width();
    int widgetY = mainWidget->height();

//    mainWidget->getScene()->setSceneRect(x - widgetX / 2, y - widgetY / 2, widgetX, widgetY);
}

void DrawingWindow::createToolMenuBar() {
    toolMenuBar = new QToolBar();
    toolMenuBar->addAction(loadFileAction);
    toolMenuBar->addAction(saveFileAction);
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
    mainWidget->getScene()->addItem(new CoordinateAxisGraphicsItem);
    GraphicsVisitor *visitor = new QtGraphicsViewVisitor(mainWidget->getScene());
    cout << "test";
    activateGraphics->accept(*visitor);
    mainWidget->getScene()->update();
    resizeScene();
}

void DrawingWindow::showWarningDialog(string message) {
    QMessageBox::warning(0, "Warning", QString(message.c_str()));
}

void DrawingWindow::doCreateSquare() {
    Shape *square = new Square(0, 0, 50);
    this->activateGraphics->add(new SimpleGraphics(square));
    updateScene();
}


