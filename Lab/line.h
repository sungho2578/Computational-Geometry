#ifndef __LINE_H
#define __LINE_H
#include "vector.h"

class Line {
public:
  double x1, y1, x2, y2;
  
  Line(double _x1, double _y1, double _x2, double _y2);
  
  Line(const Point& p1, const Point& p2);
  
  Point intersection(const Line& l2) const;
};

std::ostream& operator<<(std::ostream& out, const Line& l);
#endif
