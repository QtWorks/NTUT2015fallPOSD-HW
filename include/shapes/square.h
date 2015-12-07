#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include "shape.h"

using std::string;

class Square : public Shape {
private:
    int _llx, _lly;
    int _length;
public:
    Square(int llx, int lly, int length);

    string print();

    virtual int area() const;

    virtual BoundingBox getBoundingBox() const;

    virtual string describe();

    virtual int getX() const;

    virtual int getY() const;

    int getLength();
};

#endif // SQUARE_H
