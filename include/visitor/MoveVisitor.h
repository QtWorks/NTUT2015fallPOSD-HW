//
// Created by Raccoon on 2016/1/6.
//

#ifndef POSD_104598003_HW7_MOVEVISITOR_H
#define POSD_104598003_HW7_MOVEVISITOR_H

#include "GraphicsVisitor.h"

class MoveVisitor : public GraphicsVisitor {

public:
    MoveVisitor(int diffX, int diffY);

    virtual void visitSimpleGraphic(SimpleGraphics *graphics) override;

    virtual void visitCompositeGraphic(CompositeGraphics *graphics) override;

    virtual void visitRootGraphic(RootGraphics *graphics) override;

private:
    int diffX = 0, diffY = 0;
};


#endif //POSD_104598003_HW7_MOVEVISITOR_H
