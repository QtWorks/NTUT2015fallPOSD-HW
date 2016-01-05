//
// Created by Raccoon on 2015/12/11.
//

#ifndef POSD_104598003_HW5_UTMULTIPLEROOTGRAPHICSFACTORY_H
#define POSD_104598003_HW5_UTMULTIPLEROOTGRAPHICSFACTORY_H

#include "cppunitlite/TestHarness.h"

#include "RootGraphics.h"
#include "simplegraphics.h"
#include "circle.h"
#include "rectangle.h"
#include "square.h"

#include "DescriptionVisitor.h"
#include "MultiRootGraphicFactory.h"

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

TEST(MultipleRootGraphics, DescribeTest) {
    RootGraphics *r = new RootGraphics;
    r->add(new SimpleGraphics(new Circle(0, 0, 100)));
    r->add(new SimpleGraphics(new Square(50, 50, 100)));
    r->add(new SimpleGraphics(new Rectangle(-50, -50, 100, 200)));

    DescriptionVisitor v;
    r->accept(v);

    ostringstream oss;
    oss << "C(0,0,100)\n";
    oss << "S(50,50,100)\n";
    oss << "R(-50,-50,100,200)\n";

    CHECK(v.getDescription() == oss.str());
}

TEST(MultipleRootGraphics, FactoryTest) {
    ostringstream oss;
    oss << "C(0,0,50)\n";
    oss << "S(-100,-100,100)\n";
    oss << "R(-50,-50,50,150)\n";
    string input = oss.str();

    GraphicsFactory *gf = new MultiRootGraphicFactory;
    Graphics *g = gf->buildGraphicsFromFile("hw5_t01.txt");

    CHECK(static_cast<RootGraphics *>(g) != 0);

    DescriptionVisitor v;
    g->accept(v);

    CHECK(v.getDescription() == oss.str());

}


#endif //POSD_104598003_HW5_UTMULTIPLEROOTGRAPHICSFACTORY_H
