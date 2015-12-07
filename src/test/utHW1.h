#include "cppunitlite/TestHarness.h"

#include "shape.h"
#include "circle.h"
#include "square.h"
#include "point.h"
#include "line.h"
#include "rectangle.h"
#include "graphics.h"
#include "simplegraphics.h"
#include "compositegraphics.h"

/* below is homework #1 test cast */
TEST(areaSum, Rectangle) {
    Rectangle r1(0,0,1,2), r2(0,0,2,3),r3(0,0,3,4);
    std::vector<Shape *> v;
    v.push_back(&r1);
    v.push_back(&r2);
    v.push_back(&r3);
    LONGS_EQUAL(20,areaSum(v));
}

TEST(areaSum, allShapes) {
    Circle c(0,0,1);
    Square s(0,0,2);
    Rectangle r(0,0,3,4);
    std::vector<Shape *> v;
    v.push_back(&c);
    v.push_back(&s);
    v.push_back(&r);
    LONGS_EQUAL(19,areaSum(v));
}

TEST(Shape, getBoundingBox) {
    Circle c(0,0,1);
    Rectangle r(1,1,1,2);
    Square s(0,0,3);

    // bounding box of a shape is a rectangle
    LONGS_EQUAL(-1,c.getBoundingBox().llx());
    LONGS_EQUAL(-1,c.getBoundingBox().lly());
    LONGS_EQUAL(1,c.getBoundingBox().urx());
    LONGS_EQUAL(1,c.getBoundingBox().ury());

    LONGS_EQUAL(1,r.getBoundingBox().llx());
    LONGS_EQUAL(1,r.getBoundingBox().lly());
    LONGS_EQUAL(2,r.getBoundingBox().urx());
    LONGS_EQUAL(3,r.getBoundingBox().ury());

    LONGS_EQUAL(0,s.getBoundingBox().llx());
    LONGS_EQUAL(0,s.getBoundingBox().lly());
    LONGS_EQUAL(3,s.getBoundingBox().urx());
    LONGS_EQUAL(3,s.getBoundingBox().ury());

    LONGS_EQUAL(4,c.getBoundingBox().area());
    LONGS_EQUAL(2,r.getBoundingBox().area());
    LONGS_EQUAL(9,s.getBoundingBox().area());
}

TEST (Graphics, defaultBoundingBox) {
    Graphics g;
    // Graphics object has a default bounding box of
    // rectangle (0,0,0,0)
    LONGS_EQUAL(0,g.getBoundingBox().llx());
    LONGS_EQUAL(0,g.getBoundingBox().lly());
    LONGS_EQUAL(0,g.getBoundingBox().urx());
    LONGS_EQUAL(0,g.getBoundingBox().ury());
}

TEST (CompositeGraphics, defaultBoundingBox) {
    CompositeGraphics g;
    // CompositeGraphics object has a default bounding box of
    // rectangle (0,0,0,0)
    LONGS_EQUAL(0,g.getBoundingBox().llx());
    LONGS_EQUAL(0,g.getBoundingBox().lly());
    LONGS_EQUAL(0,g.getBoundingBox().urx());
    LONGS_EQUAL(0,g.getBoundingBox().ury());
    LONGS_EQUAL(0,g.getBoundingBox().area());
}

TEST(SimpleGraphics, ctor_BoundingBox) {
    // SimpleGraphics object points to a Shape object
    Graphics *g1 = new SimpleGraphics(new Circle(0,0,1));
    Graphics *g2 = new SimpleGraphics(new Square(0,0,2));
    Graphics *g3 = new SimpleGraphics(new Rectangle(5,6,3,4));

    LONGS_EQUAL(-1,g1->getBoundingBox().llx());
    LONGS_EQUAL(-1,g1->getBoundingBox().lly());
    LONGS_EQUAL(1,g1->getBoundingBox().urx());
    LONGS_EQUAL(1,g1->getBoundingBox().ury());

    LONGS_EQUAL(0,g2->getBoundingBox().llx());
    LONGS_EQUAL(0,g2->getBoundingBox().lly());
    LONGS_EQUAL(2,g2->getBoundingBox().urx());
    LONGS_EQUAL(2,g2->getBoundingBox().ury());

    LONGS_EQUAL(5,g3->getBoundingBox().llx());
    LONGS_EQUAL(6,g3->getBoundingBox().lly());
    LONGS_EQUAL(8,g3->getBoundingBox().urx());
    LONGS_EQUAL(10,g3->getBoundingBox().ury());

}

TEST(SimpleGraphics, AddingGraphicsObjectShouldThrowException) {
    SimpleGraphics g(new Circle(0,0,1));
    // adding Graphics throws an exception
    try {
        g.add(new Graphics);
    } catch (std::string s) {
        CHECK(std::string("Cannot add child")==s);
    }
    // adding SimpleGraphics throws an exception
    try {
        g.add(new SimpleGraphics(new Circle(0,0,1)));
    } catch (std::string s) {
        CHECK(std::string("Cannot add child")==s);
    }

    // adding CompositeGraphics throws an exception
    try {
        g.add(new CompositeGraphics);
    } catch (std::string s) {
        CHECK(std::string("Cannot add child")==s);
    }
}

TEST(CompositeGraphics, addingOneChild) {
    CompositeGraphics g;

    try {
        g.add(new SimpleGraphics(new Circle(0,0,2)));
    } catch (std::string s) {
        FAIL("Should not throw exception");
    }

    LONGS_EQUAL(16,g.getBoundingBox().area());
}

TEST(CompositeGraphics, addingTwoChildrenAndGetBoundingBox) {
    CompositeGraphics g;

    g.add(new SimpleGraphics(new Circle(0,0,1)));
    g.add(new SimpleGraphics(new Square(-2,-2,2)));

    LONGS_EQUAL(-2,g.getBoundingBox().llx());
    LONGS_EQUAL(-2,g.getBoundingBox().lly());
    LONGS_EQUAL(1,g.getBoundingBox().urx());
    LONGS_EQUAL(1,g.getBoundingBox().ury());
}

TEST(CompositeGraphics, SimpleAndCompositeChildrenAndGetBoundingBox) {
    CompositeGraphics g;
    SimpleGraphics r(new Rectangle (-1,-1,1,3));

    g.add(new SimpleGraphics(new Circle(0,0,1)));
    g.add(new SimpleGraphics(new Square(-2,-2,2)));
    CompositeGraphics h;
    h.add(&g);
    h.add(&r);

    LONGS_EQUAL(-2,h.getBoundingBox().llx());
    LONGS_EQUAL(-2,h.getBoundingBox().lly());
    LONGS_EQUAL(1,h.getBoundingBox().urx());
    LONGS_EQUAL(2,h.getBoundingBox().ury());
}
/* above is homework 1 test cast */
