#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "rectangle.h"

class BoundingBox : public Rectangle{
private:
	int _llx, _lly;
	int _l, _w;
public:
	BoundingBox(int x, int y, int w, int h);
	int llx() const;
	int lly() const;
	int urx() const;
	int ury() const;
};

#endif // BOUNDINGBOX_H
