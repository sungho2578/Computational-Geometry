#include "vector.h"
#include<math.h>

Vector::Vector() : x(std::numeric_limits<double>::quiet_NaN()),
          y(std::numeric_limits<double>::quiet_NaN()) {}

Vector::Vector(double _x, double _y) : x(_x), y(_y) {}

Vector Vector::operator+(const Vector& p2) const {
  return Vector(x + p2.x, y + p2.y);
}

Vector Vector::operator-(const Vector& p2) const {
  return Vector(x - p2.x, y - p2.y);
}

Vector Vector::operator*(double a) const {
  return Vector(x * a, y * a);
}

double Vector::cross(const Vector& v2) const {
  return this->x * v2.y - this->y * v2.x;
}

bool Vector::isValid() const {
  return isfinite(x) && isfinite(y);
}

std::ostream& operator<<(std::ostream& out, const Vector& v) {
  return out << '(' << v.x << ',' << v.y << ')';
}

