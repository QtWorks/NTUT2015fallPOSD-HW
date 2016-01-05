//
// Created by Raccoon on 2016/1/5.
//

#include "Observable.h"
#include "Observer.h"

#include <list>
using namespace std;

void Observable::addObserver(Observer *observer) {
    observers.push_back(observer);
}

void Observable::deleteObserver(Observer *observer) {
    list<Observer *>::iterator it;
    for (it = observers.begin(); it != observers.end(); it++) {
        if ((*it) == observer) {
            break;
        }
    }
    if ((*it) == observer) {
        observers.erase(it);
    }
}

void Observable::deleteObserver() {
    observers.clear();
}

void Observable::notifyObservers() {
    for (auto observer : observers) {
        observer->update();
    }
}