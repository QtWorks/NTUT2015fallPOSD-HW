//
// Created by Raccoon on 2015/12/11.
//

#ifndef POSD_104598003_HW5_ROOTGRAPHICS_H
#define POSD_104598003_HW5_ROOTGRAPHICS_H

#include "compositegraphics.h"

class RootGraphics : public CompositeGraphics {

public:
    virtual void accept(GraphicsVisitor &graphicsVisitor) override;
};

#endif //POSD_104598003_HW5_ROOTGRAPHICS_H
