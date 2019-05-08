#include "line.h"
#include <iostream>

Line::Line(double _x1, double _y1, double _x2, double _y2) :
  x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}

Line::Line(const Point& p1, const Point& p2) :
  x1(p1.x), y1(p1.y), x2(p2.x), y2(p2.y) {}

Point Line::intersection(const Line& l2) const {
  const double &x3 = l2.x1;
  const double &y3 = l2.y1;
  const double &x4 = l2.x2;
  const double &y4 = l2.y2;
  const double d = (x2-x1)*(y3-y4)-(y2-y1)*(x3-x4);
  if (d == 0)
    // No intersection
    return Point();
  double dx0 = (x2-x1)*(y3*x4-x3*y4)-(y1*x2-x1*y2)*(x4-x3);
  double x0 = dx0 / d;
  // Check if the intersection is within the two line segments
  if (x1 < x2) {
    if (x0 < x1 || x0 > x2)
      return Point();
  } else {
    if (x0 < x2 || x0 > x1)
      return Point();
  }
  if (l2.x1 < l2.x2) {
    if (x0 < l2.x1 || x0 > l2.x2)
      return Point();
  } else {
    if (x0 < l2.x2 || x0 > l2.x1)
      return Point();
  }
  
  double dy0 = (y1*x2-x1*y2)*(y3-y4)-(y1-y2)*(y3*x4-x3*y4);
  double y0 = dy0 / d;
  return Point(x0, y0);
}

std::ostream& operator<<(std::ostream& out, const Line& l) {
  return out << '(' << l.x1 << ',' << l.y1 << ")-(" << l.x2 << ',' << l.y2 << ')';
}
