#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include "shape.h"

class Square : public Shape {
private:
	int _llx, _lly;
	int _length;
public:
	Square(int llx, int lly, int length);
	string print();
	virtual int area() const;
	virtual BoundingBox getBoundingBox() const;
};

#endif // SQUARE_H
