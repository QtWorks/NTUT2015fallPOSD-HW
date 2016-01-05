//
// Created by Raccoon on 2016/1/5.
//

#ifndef POSD_104598003_HW7_UTGRAPHICSMODELOBSERVABLE_H
#define POSD_104598003_HW7_UTGRAPHICSMODELOBSERVABLE_H

#include "cppunitlite/TestHarness.h"
#include "GraphicsModel.h"
#include "Observer.h"

class MockObserver : public Observer {
public:
    bool isNotify = false;
    virtual void update() {
        this->isNotify = true;
    }
};

TEST(MockObserverTest, GraphicsModel) {
    MockObserver observer;
    CHECK(observer.isNotify == false);
}

TEST(ModelUpdateTest, GraphicsModel) {

    GraphicsModel model;
    MockObserver observer;

    model.addObserver(&observer);
    CHECK(observer.isNotify == false);

    model.loadFromFile("t1.txt");
    CHECK(observer.isNotify);

}

#endif //POSD_104598003_HW7_UTGRAPHICSMODELOBSERVABLE_H
