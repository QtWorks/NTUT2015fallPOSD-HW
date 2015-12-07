#ifndef POINT_H
#define POINT_H

#include <string>
#include "shape.h"

using std::string;

class Point : public Shape {
private:
	int _x, _y;
public:
	Point(int x, int y);
	string print();
	int getX() const;
	int getY() const;
};

#endif // POINT_H
