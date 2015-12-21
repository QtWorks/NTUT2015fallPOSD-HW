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
    string print() override;
    virtual int area() const override;
    virtual BoundingBox getBoundingBox() const override;
    virtual string describe() override;
    virtual int getX() const override;
    virtual int getY() const override;
    virtual void moveBy(int x, int y) override;

    int getLength();

};

#endif // SQUARE_H
