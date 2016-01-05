#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
private:
    int _cx, _cy;
    int _radius;
public:
    Circle(int cx, int cy, int radius);
    string print() override;
    virtual int area() const override;
    virtual BoundingBox getBoundingBox() const override;
    virtual string describe() override;
    virtual int getX() const override;
    virtual int getY() const override;
    virtual void moveBy(int x, int y) override;

    int getRadius() const;

};

#endif // CIRCLE_H
