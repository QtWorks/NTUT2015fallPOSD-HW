//
// Created by Raccoon on 2015/12/22.
//

#ifndef POSD_104598003_HW5_QTGRAPHICSTOSTANDARDITEMMODELVISITOR_H
#define POSD_104598003_HW5_QTGRAPHICSTOSTANDARDITEMMODELVISITOR_H

#include "GraphicsVisitor.h"

#include <stack>
#include <QStandardItemModel>

using std::stack;

class QtGraphicsToStandardItemModelVisitor : public GraphicsVisitor {

public:

    QtGraphicsToStandardItemModelVisitor();
    ~QtGraphicsToStandardItemModelVisitor();

    virtual void visitSimpleGraphic(SimpleGraphics *graphics) override;
    virtual void visitCompositeGraphic(CompositeGraphics *graphics) override;
    virtual void visitRootGraphic(RootGraphics *graphics) override;
    virtual void enter() override;
    virtual void leave() override;

    QStandardItemModel *getModel();

private:
    QStandardItemModel *model;
    stack<QStandardItem *> *_itemStack;
    QIcon *circleIcon;
    QIcon *squareIcon;
    QIcon *rectangleIcon;
    QIcon *compositeIcon;
};


#endif //POSD_104598003_HW5_QTGRAPHICSTOSTANDARDITEMMODELVISITOR_H
