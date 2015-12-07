#ifndef LINE_H
#define LINE_H

#include <string>
#include "shape.h"

using std::string;

class Line : public Shape {
private:
	int _bx, _by;
	int _ex, _ey;
public:
	Line(int bx, int by, int ex, int ey);
	string print();
};

#endif // LINE_H
