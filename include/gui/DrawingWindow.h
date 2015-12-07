#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QtWidgets/qmenu.h>

#include "graphics.h"
#include "DrawingArea.h"


class DrawingWindow : public QMainWindow {
Q_OBJECT
public:
    DrawingWindow();

    virtual ~DrawingWindow();

private:
    void createMenuBar();

    void initializeMenuAction();

    void createGraphicsView();

    void createToolMenuBar();

    void loadFile(std::string filename);

    void showWarningDialog(string message);

    QString getCurrentPath();

    Graphics *activateGraphics = 0;

    /**
     * Qt Objects
     */
    // Menubar Items
    QMenu *fileMenu;
    QMenu *aboutMenu;
    QMenu *createShapeMenu;

    // FileMenu action
    // for file menu
    QAction *loadFileAction;
    QAction *saveFileAction;
    // for create shape menu
    QAction *createSquareAction;
    QAction *createRectangleAction;
    QAction *createCircleAction;

    QAction *deleteSimpleGraphicAction;

    // for group action
    QAction *groupAction;
    QAction *ungroupAction;

    QToolBar *toolMenuBar;

    // AboutMenu action
    QAction *aboutDeveloperAction;

    // Main View
    DrawingArea *mainWidget;

    void updateScene();

private slots:

    void doAboutDeveloper();

    void doOpenFile();

    void doSaveFile();

    void setConnect();

    void doCreateSquare();

    void AttachAction() const;

    void resizeScene() const;
};


#endif //INC_104598003_HW4_WINDOW_H
