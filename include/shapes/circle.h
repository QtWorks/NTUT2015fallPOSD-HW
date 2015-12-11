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
	virtual int getX() const;
	virtual int getY() const;
    int getRadius() const;

	virtual void moveBy(int x, int y) override;
};

#endif // CIRCLE_H
