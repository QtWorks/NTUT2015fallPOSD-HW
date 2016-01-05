#ifndef UTTRYQT_H
#define UTTRYQT_H

#include "cppunitlite/TestHarness.h"
#include "DrawingController.h"

#include <QApplication>

TEST(tryQtMVC, gui){
    // fake argc and argv
    int argc = 1;
    char argv_01[] = "104598003_HW7.exe";
    char *argv[1] = {argv_01};


    QApplication *app = new QApplication(argc, argv);

    DrawingController main;
    main.show();

    LONGS_EQUAL(0, app->exec());
}

#endif
