#ifndef HW5_MULTIROOTGRAPHICFACTORY_H
#define HW5_MULTIROOTGRAPHICFACTORY_H

#include "GraphicsFactory.h"

class MultiRootGraphicFactory : public GraphicsFactory {

public:
    virtual Graphics *buildGraphicsFromFile(const char *fileName) override;
    virtual Graphics *buildGraphicsFromString(const char *fileName);
};


#endif //HW5_MULTIROOTGRAPHICFACTORY_H
