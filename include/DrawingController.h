//
// Created by Raccoon on 2016/1/4.
//

#ifndef POSD_104598003_HW7_DRAWINGCONTROLLER_H
#define POSD_104598003_HW7_DRAWINGCONTROLLER_H

#include "graphics.h"
#include "compositegraphics.h"

#include <QMainWindow>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QTreeView>
#include <QSplitter>

#include <string>
using std::string;

class QMainWindow;
class CommandManager;
class GraphicsModel;
class ShapeQGraphicsItem;

class DrawingController : public QMainWindow {
Q_OBJECT

public:
    DrawingController();
    virtual ~DrawingController();
    QList<QGraphicsItem *> getGraphicsItems();

public: // Controller Event Handler
    void onItemSelected();
    void onItemMove(ShapeQGraphicsItem *item, int diffX, int diffY);

public:
    /**
     * for selected behavior
     */
    void setSelectedTarget(Graphics *target, CompositeGraphics *parentContainer);
    void clearSelectd();
    bool hasSelectedTarget();

    CompositeGraphics *getSelectedParent();
    Graphics *getSelectedTarget();

private: // helper method
    QString getCurrentPath();
    void showWarningDialog(string message);
    void updateScene();
    void updateActionState();

    bool canGroup();
    bool canUngroup();
    bool canDelete();
    bool canUpperLayer();
    bool canLowerLayer();

private: // controller setup action
    void initializeView();

    void initializeAction();
    void setConnect();

    void createMenuBar();
    void attachMenuAction();

    void createToolMenuBar();
    void attachToolMenuAction();

    void createCentralWidget();

private: // model and commandManager
    GraphicsModel *_model;
    CommandManager *_commandManager;

    Graphics *selectedTarget = 0;
    CompositeGraphics *selectedParent = 0;

    bool isDirty = false;

private: // view object
    // Menubar Items
    QMenu *fileMenu;
    QMenu *aboutMenu;
    QMenu *createShapeMenu;
    // toolbar
    QToolBar *toolMenuBar;
    // FileMenu action
    // for file menu
    QAction *loadFileAction;
    QAction *saveFileAction;
    // for command
    QAction *redoAction;
    QAction *undoAction;
    // for create shape menu
    QAction *createSquareAction;
    QAction *createRectangleAction;
    QAction *createCircleAction;
    // for delete
    QAction *deleteSimpleGraphicAction;
    // for group action
    QAction *groupAction;
    QAction *ungroupAction;
    // for layer
    QAction *upperLayerAction;
    QAction *lowerLayerAction;
    // AboutMenu action
    QAction *aboutDeveloperAction;

    //Widget
    QSplitter *centralWidget;

    QGraphicsView *view;
    QGraphicsScene *scene;
    QTreeView *treeView;

private slots: // view action
    void doOpenFile();
    void doSaveFile();

    void doUndo();
    void doRedo();

    void doCreateSquare();
    void doCreateCircle();
    void doCreateRectangle();

    void doDeleteSimpleGraphics();

    void doGroup();
    void doUnGroup();

    void doUpperLayer();
    void doLowerLayer();

    void doAboutDeveloper();
};

#endif //POSD_104598003_HW7_DRAWINGCONTROLLER_H
