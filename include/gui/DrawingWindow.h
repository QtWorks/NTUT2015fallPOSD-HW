#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QVBoxLayout>

#include "graphics.h"
#include "DrawingArea.h"


class DrawingWindow : public QMainWindow{
    Q_OBJECT
public:
    DrawingWindow();
    virtual ~DrawingWindow();

    void createMenuBar();

    void initializeMenuAction();

    void createGraphicsView();

    void createToolMenuBar();
protected:
private:

    Graphics *activateGraphics = 0;

    void loadFileToDisplay(std::string filename);

    /**
     * Qt Objects
     */
    // Menubar Items
    QMenu *fileMenu;
    QMenu *aboutMenu;

    // FileMenu action
    QAction *loadFileAction;
    QAction *saveFileAction;
    QToolBar *toolMenuBar;

    // AboutMenu action
    QAction *aboutDeveloperAction;

    // Main View
    DrawingArea *mainWidget;

private slots:
    void doAboutDeveloper();
    void doOpenFile();
    void doSaveFile();
    void setConnect();

    void showWarningDialog(string message);

    QString getCurrentPath();
};


#endif //INC_104598003_HW4_WINDOW_H
