#include "polygon.h"

const Point& Points::operator[](int i) const {
  return at((i + size()) % size());
}
