#ifndef UTGRAPHICFACTORY_H
#define UTGRAPHICFACTORY_H

#include <cppunitlite/TestHarness.h>

#include <iostream>

#include "simplegraphics.h"
#include "compositegraphics.h"
#include "circle.h"
#include "square.h"
#include "DescriptionVisitor.h"
#include "GraphicsVisitor.h"

#include <stdio.h>

using namespace std;

TEST(DescriptorVisitor, ComplexGraphicTest01) {


    std::string ans("Comp R(-300,-300,600,600)\n");
    ans += std::string("  C(0,0,300)\n");
    ans += std::string("  Comp R(-200,-200,400,400)\n");
    ans += std::string("    Comp R(-200,-200,400,400)\n");
    ans += std::string("      Comp R(-200,-200,400,400)\n");
    ans += std::string("        Comp R(-200,-200,400,400)\n");
    ans += std::string("          S(-200,-200,200)\n");
    ans += std::string("          Comp R(0,0,0,0)\n");
    ans += std::string("            Comp R(0,0,0,0)\n");
    ans += std::string("              Comp R(0,0,0,0)\n");
    ans += std::string("                Comp R(0,0,0,0)\n");
    ans += std::string("                  Comp R(0,0,0,0)\n");
    ans += std::string("          S(0,0,200)\n");
    ans += std::string("      Comp R(-100,-100,200,200)\n");
    ans += std::string("        S(-100,-100,200)\n");

    Graphics *g0 = new CompositeGraphics();
    Graphics *g1 = new CompositeGraphics();
    Graphics *g2 = new CompositeGraphics();
    Graphics *g3 = new CompositeGraphics();
    Graphics *g4 = new CompositeGraphics();
    Graphics *g5 = new CompositeGraphics();
    Graphics *g6 = new CompositeGraphics();
    Graphics *g7 = new CompositeGraphics();
    Graphics *g8 = new CompositeGraphics();
    Graphics *g9 = new CompositeGraphics();
    Graphics *g11 = new CompositeGraphics();

    g0->add(new SimpleGraphics(new Circle(0, 0, 300)));
    g0->add(g1);
    g1->add(g2);
    g2->add(g3);
    g3->add(g4);
    g4->add(new SimpleGraphics(new Square(-200, -200, 200)));
    g4->add(g5);
    g4->add(new SimpleGraphics(new Square(0, 0, 200)));
    g5->add(g6);
    g6->add(g7);
    g7->add(g8);
    g8->add(g9);
    g11->add(new SimpleGraphics(new Square(-100, -100, 200)));
    g2->add(g11);

    DescriptionVisitor dv;
    g0->accept(dv);
    CHECK(ans == dv.getDescription());
}

#endif

