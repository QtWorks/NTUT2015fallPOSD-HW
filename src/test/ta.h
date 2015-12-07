#ifndef UTHW3_TA_H_INCLUDED
#define UTHW3_TA_H_INCLUDED

#include "cppunitlite/TestHarness.h"
#include <string>
#include "Circle.h"
#include "Square.h"
#include "Rectangle.h"
#include "Graphics.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include <string>
#include <vector>
#include "AreaVisitor.h"
#include "DescriptionVisitor.h"
#include "GraphicsFactory.h"

using namespace std;
TEST (GraphicsFactory, buildGraphicsFromFile_f1) {
    GraphicsFactory gf;
	Graphics * graphics = gf.buildGraphicsFromFile("f1.txt");
    DescriptionVisitor dv;
    graphics->accept(dv);

    std::string ans("Comp R(-2,-2,3,4)\n");
    ans += std::string("  Comp R(-2,-2,3,3)\n");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==dv.getDescription());
}
TEST (GraphicsFactory, buildGraphicsFromFile_t1) {
    GraphicsFactory gf;
    Graphics * graphics = gf.buildGraphicsFromFile("t1.txt");

    DescriptionVisitor dv;
    graphics->accept(dv);

    std::string ans("Comp R(-2,-2,3,4)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    ans += std::string("  Comp R(-2,-2,3,3)\n");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    CHECK(ans==dv.getDescription());
}

TEST (GraphicsFactory, buildGraphicsFromFile_t2) {
    GraphicsFactory gf;
    Graphics * graphics = gf.buildGraphicsFromFile("t2.txt");

    DescriptionVisitor dv;
    graphics->accept(dv);

    std::string ans("Comp R(-2,-2,3,4)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    ans += std::string("  C(0,0,1)\n");
    ans += std::string("  S(-2,-2,2)\n");
     ans += std::string("  Comp R(0,0,0,0)\n");
    CHECK(ans==dv.getDescription());
}

TEST (GraphicsFactory, buildGraphicsFromFile_t3) {
    GraphicsFactory gf;
    Graphics * graphics = gf.buildGraphicsFromFile("t3.txt");

    DescriptionVisitor dv;
    graphics->accept(dv);

    std::string ans("R(-1,-1,1,3)\n");
    CHECK(ans==dv.getDescription());
}

#endif // UTHW3_H_INCLUDED
