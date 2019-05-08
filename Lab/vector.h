#ifndef __VECTOR_H
#define __VECTOR_H
#include<limits>
#include<iostream>

struct Vector {
  double x, y;
  
  Vector();
  
  Vector(double _x, double _y);
  
  /** Vector addition */
  Vector operator+(const Vector& p2) const;
  
  /** Vector subtraction */
  Vector operator-(const Vector& p2) const;
  
  /** Scalar multiplication */
  Vector operator*(double a) const;
  
  double cross(const Vector& v2) const;
  
  /**Return true if the vector stores valid (finite) numbers*/
  bool isValid() const;
};

std::ostream& operator<<(std::ostream& out, const Vector& v);

// Make Point a synonym of Vector
typedef Vector Point;
#endif
