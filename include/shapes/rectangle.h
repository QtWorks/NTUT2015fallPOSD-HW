#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include "shape.h"
#include "point.h"

class Rectangle : public Shape {
private:
    Point _llc;
    int _l, _w;
public:
    Rectangle(int x, int y, int w, int h);
    Rectangle(Point p, int w, int h);

    string print() override;
    int area() const override;
    virtual BoundingBox getBoundingBox() const override;
    virtual string describe() override;
    virtual int getX() const override;
    virtual int getY() const override;
    virtual void moveBy(int x, int y) override;

    int getWidth();
    int getHeight();


};

#endif // RECTANGLE_H
