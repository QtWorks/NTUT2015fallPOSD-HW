#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::ostream;

class BoundingBox;

class Shape {
private:
	string _name;
public:
	Shape(string name);
	string name();
	virtual string print();
	virtual int area() const;
	virtual BoundingBox getBoundingBox() const;
};

string printShape(vector<Shape *> shapes);
int areaSum(vector<Shape *> shapes);
ostream & operator << (ostream & os, Shape & s);

#endif // SHAPE_H
