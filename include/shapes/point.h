#ifndef POINT_H
#define POINT_H

#include "shape.h"

#include <string>
using std::string;

class Point : public Shape {
private:
	int _x, _y;
public:
	Point(int x, int y);
	string print();
	int getX() const;
	int getY() const;
	void setX(int _x);
	void setY(int _y);
};

#endif // POINT_H
