
#ifndef POSD_104598003_HW7_GRAPHICSMODEL_H
#define POSD_104598003_HW7_GRAPHICSMODEL_H

#include "RootGraphics.h"
#include "Observable.h"

class GraphicsModel : public Observable {

public:
    GraphicsModel();
    ~GraphicsModel();

    bool loadFromFile(const char *filename);
    bool saveToFile(const char *filename);

    RootGraphics *getModel();

private:
    RootGraphics *root;
};

#endif