#include "circle.h"
#include "shape.h"
#include "boundingbox.h"

#include <vector>
#include <sstream>
using std::vector;

Shape::Shape(string name)
        : _name(name) { }

string Shape::name() {
    return _name;
}

string Shape::print() {
    return name();
}

int Shape::area() const {
    return 0;
}

ostream &operator<<(ostream &os, Shape &s) {
    return os << s.print();
}

string printShape(vector<Shape *> shapes) {
    std::ostringstream oss;
    for (unsigned int i = 0; i < shapes.size(); ++i)
        oss << shapes[i]->print() << "\n";
    return oss.str();
}

int areaSum(vector<Shape *> shapes) {
    int area = 0;
    for (vector<Shape *>::iterator iter = shapes.begin(); iter != shapes.end(); ++iter) {
        area += (*iter)->area();
    }
    return area;
}

BoundingBox Shape::getBoundingBox() const {
    BoundingBox box(0, 0, 0, 0);
    return box;
}

void Shape::moveBy(int x, int y) {
}