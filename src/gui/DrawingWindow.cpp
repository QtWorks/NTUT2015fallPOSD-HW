#include "DrawingWindow.h"

#include <iostream>
#include <fstream>

#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QtWidgets/qtoolbutton.h>

#include "QtGraphicsViewVisitor.h"
#include "DescriptionVisitor.h"
#include "GraphicsFactory.h"

#include "compositegraphics.h"
#include "simplegraphics.h"

using namespace std;

DrawingWindow::DrawingWindow() {
    this->setWindowTitle("POSD Homework#4");
    this->resize(800, 600);

    createMenuBar();
    createToolMenuBar();
    createGraphicsView();
}


DrawingWindow::~DrawingWindow() {

}

void DrawingWindow::createMenuBar() {
    fileMenu = this->menuBar()->addMenu("File");
    aboutMenu = this->menuBar()->addMenu("About");
    initializeMenuAction();

}

void DrawingWindow::initializeMenuAction() {
    loadFileAction = new QAction(QIcon("./icon/Open.png"), "loadFile", this);
    saveFileAction = new QAction(QIcon("./icon/Save.png"), "saveFile", this);
    aboutDeveloperAction = new QAction("aboutDeveloper", this);

    setConnect();

    fileMenu->addAction(loadFileAction);
    fileMenu->addAction(saveFileAction);
    aboutMenu->addAction(aboutDeveloperAction);
}

void DrawingWindow::setConnect() {
    connect(aboutDeveloperAction, SIGNAL(triggered(bool)), this, SLOT(doAboutDeveloper()));
    connect(loadFileAction, SIGNAL(triggered(bool)), this, SLOT(doOpenFile()));
    connect(saveFileAction, SIGNAL(triggered(bool)), this, SLOT(doSaveFile()));
}

void DrawingWindow::createGraphicsView() {
    mainWidget = new DrawingArea();
    this->setCentralWidget(mainWidget);
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

    if(filename == ""){
        showWarningDialog("Not Selected any file");
        return;
    }
    loadFileToDisplay(filename.toUtf8().constData());
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

        filename = QFileDialog::getSaveFileName(this, "Choose Save Path and Name", currentPath, "Graphics Files (*.txt)");

        if(filename == ""){
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

void DrawingWindow::loadFileToDisplay(std::string filename) {

    mainWidget->getScene()->clear();

    GraphicsVisitor *visitor = new QtGraphicsViewVisitor(mainWidget->getScene());
    GraphicsFactory graphicsFactory;

    try {
        Graphics *graphics = graphicsFactory.buildGraphicsFromFile(filename.c_str());
        this->activateGraphics = graphics;
    } catch (std::string e) {
        cout << e << endl;
        showWarningDialog(e);
        return;
    }

    activateGraphics->accept(*visitor);
    mainWidget->getScene()->update();
}

void DrawingWindow::showWarningDialog(string message) {
    QMessageBox::warning(0, "Warning", QString(message.c_str()));
}
