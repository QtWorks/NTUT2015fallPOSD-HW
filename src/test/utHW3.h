#ifndef UTHW3_H_INCLUDED
#define UTHW3_H_INCLUDED

#include "cppunitlite/TestHarness.h"

#include <sstream>
#include <iostream>
#include <typeinfo>
#include "GraphicsFactory.h"
#include "graphics.h"
#include "compositegraphics.h"
#include "simplegraphics.h"
#include "DescriptionVisitor.h"
#include "circle.h"
#include "square.h"
#include "rectangle.h"

using namespace std;

// For the function buildGraphicsFromFile
// throw an exception if the file does not exist.
TEST(GraphicsFactory, TestReadFileNotExist){
    GraphicsFactory gf;
    try{
        Graphics *result = gf.buildGraphicsFromFile("xxxxxxxxxx.txt");
        FAIL("Shout be have exception.");
    }catch(string s){
        CHECK(s == "File does not exist.");
    }
}
// return a correctly constructed compositeGraphics
TEST(GraphicsFactory, TestBuildGraphicsFromFile){
    GraphicsFactory gf;
    Graphics *result = gf.buildGraphicsFromFile("f1.txt");
    DescriptionVisitor dv;
    result->accept(dv);

    stringstream ss;
    ss << "Comp R(-2,-2,3,4)\n"
        << "  Comp R(-2,-2,3,3)\n"
        << "    C(0,0,1)\n"
        << "    S(-2,-2,2)\n"
        << "  R(-1,-1,1,3)\n";
    CHECK(dv.getDescription() == ss.str());
}

// For the function fileContentsAsString
// check that the file content is read into a string correctly
TEST(GraphicsFactory, TestReadFileF1_txt){
    GraphicsFactory gf;

    string result = gf.fileContentsAsString("f1.txt");

    stringstream ss;
    ss << "Comp R(-2,-2,3,4)\n"
        << "  Comp R(-2,-2,3,3)\n"
        << "    C(0,0,1)\n"
        << "    S(-2,-2,2)\n"
        << "  R(-1,-1,1,3)\n";

    string expectResult = ss.str();
    CHECK(expectResult == result);
}

// For the function extractGraphicsFromOneLine
// check SimpleGraphics with circle
TEST(GraphicsFactory, TestExtractGraphicsFromOneLine_SimpleGraphics_Basic_Circle){
    GraphicsFactory gf;
    string simpleCircleContent = "C(0,0,1)";
    int level = -1;
    Graphics *g = gf.extractGraphicsFromOneLine(simpleCircleContent,level);
    CHECK("C(0,0,1)" == (static_cast<SimpleGraphics *>(g))->getShape()->describe());
    CHECK(level == 0);
}

TEST(GraphicsFactory, TestExtractGraphicsFromOneLine_SimpleGraphics_Level3_Circle){
    GraphicsFactory gf;
    string simpleCircleContent = "      C(3030,2020,100)";
    int level = -1;
    Graphics *g = gf.extractGraphicsFromOneLine(simpleCircleContent,level);
    CHECK("C(3030,2020,100)" == (static_cast<SimpleGraphics *>(g))->getShape()->describe());
    CHECK(level == 3);
}
// check SimpleGraphics with Rectangle
TEST(GraphicsFactory, TestExtractGraphicsFromOneLine_SimpleGraphics_Basic_Rectangle){
    GraphicsFactory gf;
    string simpleCircleContent = "R(0,0,1,1)";
    int level = -1;
    Graphics *g = gf.extractGraphicsFromOneLine(simpleCircleContent,level);
    CHECK("R(0,0,1,1)" == (static_cast<SimpleGraphics *>(g))->getShape()->describe());
    CHECK(level == 0);
}

TEST(GraphicsFactory, TestExtractGraphicsFromOneLine_SimpleGraphics_Level2_Rectangle){
    GraphicsFactory gf;
    string simpleCircleContent = "    R(5,5,99999,99999)";
    int level = -1;
    Graphics *g = gf.extractGraphicsFromOneLine(simpleCircleContent,level);
    CHECK("R(5,5,99999,99999)" == (static_cast<SimpleGraphics *>(g))->getShape()->describe());
    CHECK(level == 2);
}
// check SimpleGraphics with Square
TEST(GraphicsFactory, TestExtractGraphicsFromOneLine_SimpleGraphics_Basic_Square){
    GraphicsFactory gf;
    string simpleCircleContent = "S(100,100,100)";
    int level = -1;
    Graphics *g = gf.extractGraphicsFromOneLine(simpleCircleContent,level);
    CHECK("S(100,100,100)" == (static_cast<SimpleGraphics *>(g))->getShape()->describe());
    CHECK(level == 0);
}

TEST(GraphicsFactory, TestExtractGraphicsFromOneLine_SimpleGraphics_Level5_Square){
    GraphicsFactory gf;
    string simpleCircleContent = "          S(10,10,10)";
    int level = -1;
    Graphics *g = gf.extractGraphicsFromOneLine(simpleCircleContent,level);
    CHECK("S(10,10,10)" == (static_cast<SimpleGraphics *>(g))->getShape()->describe());
    CHECK(level == 5);
}
// check SimpleGraphics with Unknown Shape
TEST(GraphicsFactory, TestExtractGraphicsFromOneLine_SimpleGraphics_Unknown_Shape){
    GraphicsFactory gf;
    string simpleCircleContent = "          G(10,10,10)";
    int level = -1;
    try{
        Graphics *g = gf.extractGraphicsFromOneLine(simpleCircleContent,level);
        FAIL("Shout be throw exception");
    }catch(string e){
        CHECK(e == string("Unknown Shape"));
    }
}
// check CompositeGraphic is returned correctly
TEST(GraphicsFactory, TestExtractGraphicsFromOneLine_Basic_CompositeGraphic){
    GraphicsFactory gf;
    string simpleCircleContent = "Comp R(10,20,30,1)";
    int level = -1;
    Graphics *g = gf.extractGraphicsFromOneLine(simpleCircleContent,level);
    // if return type g is type of compositeGraphic , do dynamic cast shout be
    // return pointer to point to the object
    CompositeGraphics *cg = dynamic_cast<CompositeGraphics *>(g);
    if(cg == 0){
        FAIL("Return Type Error");
    }
}

// For the function compose,
// check the snapshot after line 5 above
TEST(GraphicsFactory, TestComposeForLine5){
    GraphicsFactory gf;
    stack<pair<int,Graphics *>> &innerStack = gf.getBuildStack();
    innerStack.push(make_pair(0, new CompositeGraphics));
    innerStack.push(make_pair(1, new CompositeGraphics));
    innerStack.push(make_pair(2, new SimpleGraphics(new Circle(0,0,1))));
    innerStack.push(make_pair(2, new SimpleGraphics(new Square(-2,-2,2))));
    gf.compose();
    innerStack.push(make_pair(2, new SimpleGraphics(new Rectangle(-1,-1,1,3))));

    // check total object in stack
    CHECK(gf.getBuildStack().size() == 3);

    // check the top object is R(-1,-1,1,3);
    SimpleGraphics * sg = static_cast<SimpleGraphics *>(get<1>(gf.getBuildStack().top()));
    CHECK( sg->getShape()->describe()== "R(-1,-1,1,3)");
    gf.getBuildStack().pop();

    // Check the second object is Compose that contain circle and square
    DescriptionVisitor dv;
    (static_cast<CompositeGraphics *>(get<1>(gf.getBuildStack().top())))->accept(dv);
    CHECK(dv.getDescription() == "Comp R(-2,-2,3,3)\n  C(0,0,1)\n  S(-2,-2,2)\n");
    gf.getBuildStack().pop();

    // check the latest object is empty compose
    DescriptionVisitor dv2;
    (static_cast<CompositeGraphics *>(get<1>(gf.getBuildStack().top())))->accept(dv2);
    CHECK(dv2.getDescription() == "Comp R(0,0,0,0)\n");
}

// For the function compose,
// check the snapshot after line 8 above
TEST(GraphicsFactory, TestComposeForLine8){
    GraphicsFactory gf;
    gf.buildGraphicsFromFile("f1.txt");

    // at line 8 processed, stack must have only 1 obj
    CHECK(gf.getBuildStack().size() == 1);

    // check the object is correctly
    Graphics *result = get<1>(gf.getBuildStack().top());
    DescriptionVisitor dv;
    result->accept(dv);

    stringstream ss;
    ss << "Comp R(-2,-2,3,4)\n"
        << "  Comp R(-2,-2,3,3)\n"
        << "    C(0,0,1)\n"
        << "    S(-2,-2,2)\n"
        << "  R(-1,-1,1,3)\n";
    CHECK(dv.getDescription() == ss.str());
}

#endif // UTHW3_H_INCLUDED
