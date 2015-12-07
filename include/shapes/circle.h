#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>
#include "shape.h"

class Circle : public Shape {
private:
	int _cx, _cy;
	int _radius;
public:
	Circle(int cx, int cy, int radius);
	string print();
	virtual int area() const;
	virtual BoundingBox getBoundingBox() const;
	virtual string describe();
    int getX() const;
    int getY() const;
    int getRadius() const;
};

#endif // CIRCLE_H
