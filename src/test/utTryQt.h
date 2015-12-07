#ifndef UTTRYQT_H
#define UTTRYQT_H

#include "cppunitlite/TestHarness.h"
#include <QApplication>
#include "DrawingWindow.h"

TEST(tryQt, gui){
    // fake argc and argv
    int argc = 1;
    char argv_01[] = "104598003_HW4.exe";
    char *argv[1] = {argv_01};


    QApplication *app = new QApplication(argc, argv);
    DrawingWindow *window = new DrawingWindow();
    window->show();
    LONGS_EQUAL(0, app->exec());
}

#endif
