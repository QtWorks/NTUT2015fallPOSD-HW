//
// Created by Raccoon on 2016/1/5.
//

#include "GraphicsModel.h"
#include "RootGraphics.h"
#include "MultiRootGraphicFactory.h"
#include "DescriptionVisitor.h"

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

GraphicsModel::GraphicsModel() {
    this->root = new RootGraphics;
}

GraphicsModel::~GraphicsModel() {

}

bool GraphicsModel::loadFromFile(const char *filename) {
    MultiRootGraphicFactory graphicFactory;
    try {
        Graphics *g = graphicFactory.buildGraphicsFromFile(filename);
        if (dynamic_cast<RootGraphics *>(g)) {
            delete this->root;
            this->root = dynamic_cast<RootGraphics *>(g);
            this->notifyObservers();
            return true;
        } else {
            return false;
        }
    } catch (string e) {
        cout << e << endl;
        return false;
    }
}

bool GraphicsModel::saveToFile(const char *filename) {
    if (root) {
        DescriptionVisitor visitor;
        this->root->accept(visitor);
        string contents = visitor.getDescription();

        ofstream ofs;
        ofs.open(filename);
        if (ofs.is_open()) {
            ofs << contents;
            ofs.close();
            return true;
        }
    }
    return false;
}

RootGraphics *GraphicsModel::getModel() {
    return this->root;
}
