//
// Created by Raccoon on 2016/1/5.
//

#ifndef POSD_104598003_HW7_OBSERVABLE_H
#define POSD_104598003_HW7_OBSERVABLE_H

#include <list>
using std::list;

class Observer;

class Observable {
public:
    void addObserver(Observer *observer);
    void deleteObserver(Observer *observer);
    void deleteObserver();

protected:
    void notifyObservers();

private:
    list<Observer *> observers;
};


#endif //POSD_104598003_HW7_OBSERVABLE_H
