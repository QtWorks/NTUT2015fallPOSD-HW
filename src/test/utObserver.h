//
// Created by Raccoon on 2016/1/5.
//

#ifndef POSD_104598003_HW7_UTOBSERVER_H
#define POSD_104598003_HW7_UTOBSERVER_H

#include "cppunitlite/TestHarness.h"
#include "Observable.h"
#include "Observer.h"

namespace ObserverTest {

    class MockModel : public Observable {
    private:
        int data = 0;
    public:
        void setData(int v) {
            data = v;
            this->notifyObservers();
        }

        int getData() const {
            return data;
        }
    };

    class MockView : public Observer {
    public:
        bool isNotify = false;

        virtual void update() override {
            this->isNotify = true;
        }
    };

    TEST(ObserverTest, ObserverPattern) {
        MockModel model;
        MockView view;
        CHECK(view.isNotify == false);
        model.addObserver(&view);
        CHECK(view.isNotify == false);
        model.setData(10); // change model data
        CHECK(view.isNotify == true); // view has been notify
        CHECK(model.getData() == 10);
    }

}

#endif //POSD_104598003_HW7_UTOBSERVER_H
