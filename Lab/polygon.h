#ifndef __POLYGON_H
#define __POLYGON_H
#include "vector.h"
#include <vector>

class Points : public std::vector<Point> {
public:
  int x, y;
  /**
   * Return point #i in the polygon in a circular way so point #0 == point #n
   */
  const Point& operator[](int i) const;
};

typedef Points Polyline, Polygon;

#endif
