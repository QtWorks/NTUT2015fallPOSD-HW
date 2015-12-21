#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::ostream;

class BoundingBox;

class GraphicsVisitor;

class Shape {
private:
    string _name;
public:
    Shape(string name);

    string name();

    virtual string print();

    virtual int area() const;

    virtual BoundingBox getBoundingBox() const;

    virtual string describe() { return string(""); };

    virtual int getX() const { return 0; }

    virtual int getY() const { return 0; }

    virtual void moveBy(int x, int y);
};

string printShape(vector<Shape *> shapes);

int areaSum(vector<Shape *> shapes);

ostream &operator<<(ostream &os, Shape &s);

#endif // SHAPE_H
