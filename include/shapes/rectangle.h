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
	string print();
	int area() const;
	virtual BoundingBox getBoundingBox() const;
	virtual string describe();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
};

#endif // RECTANGLE_H
