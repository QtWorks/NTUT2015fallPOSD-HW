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

#include <stack>
#include "Command.h"
#include "CreateCircleCmd.h"
#include "CreateRectangleCmd.h"
#include "CreateSquareCmd.h"
#include "DeleteCmd.h"
#include "GroupCmd.h"
#include "UnGroupCmd.h"

using std::stack;


class DrawingWindow : public QMainWindow {
Q_OBJECT
public:
    DrawingWindow();

    virtual ~DrawingWindow();

    stack<Command *> command_undoCmds;
    stack<Command *> command_redoCmds;

    Graphics *activateGraphics = 0;

    void doCreateSquare();
    void doCreateCircle();
    void doCreateRectangle();
    void doGroup();
    void doUnGroup();
    void doDeleteSimpleGraphics();
    void updateScene();

    void doCmdMovePre();
    void doCmdMove();

private:
    void createMenuBar();

    void initializeMenuAction();

    void createGraphicsView();

    void createToolMenuBar();

    void loadFile(std::string filename);

    void showWarningDialog(string message);

    QString getCurrentPath();



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

    // for group action
    QAction *groupAction;
    QAction *ungroupAction;

    QAction *deleteSimpleGraphicAction;

    QAction *redoAction;
    QAction *undoAction;

    QToolBar *toolMenuBar;

    // AboutMenu action
    QAction *aboutDeveloperAction;

    // Main View
    DrawingArea *mainWidget;



private slots:

    void doAboutDeveloper();

    void doOpenFile();
    void doSaveFile();

    void doCmdCreateSquare();
    void doCmdCreateCircle();
    void doCmdCreateRectangle();
    void doCmdGroup();
    void doCmdUnGroup();
    void doCmdDeleteSimpleGraphics();

    void doUndo();
    void doRedo();

    void setConnect();

    void AttachAction() const;
    void resizeScene() const;
    void clearRedoStack();
};


#endif //INC_104598003_HW4_WINDOW_H
