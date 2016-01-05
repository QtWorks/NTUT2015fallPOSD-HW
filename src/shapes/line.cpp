#include "line.h"

#include <sstream>

Line::Line(int bx, int by, int ex, int ey)
        : Shape("line"), _bx(bx), _by(by), _ex(ex), _ey(ey) { }

string Line::print() {
    std::ostringstream oss;
    oss << name() << "(" << _bx << "," << _by << "," << _ex << "," << _ey << ")";
    return oss.str();
}
