/*
    UCR Spring 2019
    CS 133 Lab 6 - Convex Polygon
    Sungho Ahn, 862026328
*/

#include "vector.h"
#include "line.h"
#include "polygon.h"
#include <iostream>
#include <math.h>

// A macro that tests if two values are equal (mod N)
#define eqModN(x,y,n) (((x)-(y))%((signed)(n)) == 0)

// A helper function to print a pair to the output
template<typename T1,typename T2>
std::ostream& operator<<(std::ostream& out, const std::pair<T1,T2>& p) {
  return out << '(' << p.first << ',' << p.second << ')';
}

// A helper function that prints a vector to the output
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
  out << '[';
  for (int i = 0; i < v.size(); i++) {
    if (i > 0)
      out << ',' << ' ';
    out << v[i];
  }
  out << ']';
  return out;
}

/**
 * A data structure that stores one intersection point between two polygons.
 */
struct IntersectionPoint {
  // The coordinates of the intersection point
  Point point;
  // The index of the starting point of the intersecting line segment in the first polygon
  int i1;
  // The index of the starting point of the intersecting line segment in the second polygon
  int i2;

  IntersectionPoint() {}

  IntersectionPoint(const Point& _p, int _i1, int _i2) :
    point(_p), i1(_i1), i2(_i2) {}
};

// A helper function that prints the intersection point to the output
std::ostream& operator<<(std::ostream& out, const IntersectionPoint& i) {
  return out << '<' << i.point << ',' << i.i1 << ',' << i.i2 << '>';
}

// Finds the index of the top and bottom points of a polygon and returns the pair
// (iTop, iBottom) for the indexes of the top and bottom points, respectively.
std::pair<int, int> findTopAndBottomPoints(const Polygon& p) {
  // TODO

  int iTop = 0;		// Init to zero
  int iBottom = 0;	// Init to zero

  for (int i = 0; i < p.size(); i++) {
    if (p[i].y > p[iTop].y) {	// Loop through the points in polygon
      iTop = i;			// and find the highest & lowest y,
    }				// then save their index accordingly.
    if (p[i].y < p[iBottom].y) {
      iBottom = i;
    }
  }

  return std::make_pair(iTop, iBottom);	// return the index in the given form
}

/**
 * Compute the intersection between the left parts of two convex polygons.
 * Both convex hulls are stored in CCW order.
 * p1 is the first polygon.
 * tb1 the top and bottom points of the first polygon (top, bottom)
 * p2 is the second polygon.
 * tb2 the top and bottom points of the second polygon (top, bottom)
 * intersections is the list in which the intersections will be written
 */
void computeLeftLeftIntersection(const Polygon& p1, std::pair<int, int> tb1,
          const Polygon& p2, std::pair<int, int> tb2,
          std::vector<IntersectionPoint>& intersections) {
  // TODO
  std::cout << std::endl;
  std::cout << "##### LEFT-LEFT #####" << std::endl;

  IntersectionPoint inter;
  int i = tb1.first;	// Init starting index of p1 to its top point
  int j = tb2.first;	// Init starting index of p2 to its top point
  int p1bot = tb1.second;	// Retrieve bottom point index
  int p2bot = tb2.second;	// Retrieve bottom point index

  while (true) {		// Loop until both polygons arrive at their bottom points
    if ((p1[i].x == p1[p1bot].x && p1[i].y == p1[p1bot].y) || (p2[j].x == p2[p2bot].x && p2[j].y == p2[p2bot].y)) { break; }
    if (i == p1.size()) { i = 0; }	// When current index reaches the end of the list,
    if (j == p2.size()) { j = 0; }	// reset it to the starting index for correct index return.

    					// Calculate intersection point between the two lines segments.
    inter.point = Line(p1[i].x,p1[i].y,p1[i+1].x,p1[i+1].y).intersection(Line(p2[j].x,p2[j].y,p2[j+1].x,p2[j+1].y));
    inter.i1 = i;	// Set intersection point in the given form:
    inter.i2 = j;	// (coordinates of intersection point, index of S.P of line in p1, index of S.P of line in p2)

    std::cout << "i: " << i << std::endl;
    std::cout << "j: " << j << std::endl;		// index tracker for visual check
    std::cout << "inter: " << inter << std::endl;	// intersection point tracker for visual check

    if (!std::isnan(inter.point.x) && !std::isnan(inter.point.y)) {
      intersections.push_back(inter);	// If intersection point between two line segments is not a NaN,
    }					// meaning inter points does exist, push the result into the list.

    if (p1[i+1].y > p2[j+1].y)		// If end point of line1(p1) is above that of line2(p2),
      i++;				// only p1 proceeds to the next line.
    else if (p2[j+1].y > p1[i+1].y)	// If end point of line2(p2) is above that of line1(p1),
      j++;				// only p2 proceeds to the next line.
    else				// If both are on the same y,
      i++;				// proceed any of the two. In this case choose p1.
  }
}

/* Computes the intersection points of the two right halves of two convex polygons*/
void computeRightRightIntersection(const Polygon& p1, std::pair<int, int> tb1,
          const Polygon& p2, std::pair<int, int> tb2,
          std::vector<IntersectionPoint>& intersections) {
  // TODO
  std::cout << std::endl;
  std::cout << "##### RIGHT-RIGHT #####" << std::endl;

  IntersectionPoint inter;
  int i = tb1.second;	// for Right-Right, starting from the bottom to the top point
  int j = tb2.second;
  int p1top = tb1.first;
  int p2top = tb2.first;

  while (true) {
    if ((p1[i].x == p1[p1top].x && p1[i].y == p1[p1top].y) || (p2[j].x == p2[p2top].x && p2[j].y == p2[p2top].y)) { break; }
    if (i == p1.size()) { i = 0; }
    if (j == p2.size()) { j = 0; }

    inter.point = Line(p1[i].x,p1[i].y,p1[i+1].x,p1[i+1].y).intersection(Line(p2[j].x,p2[j].y,p2[j+1].x,p2[j+1].y));
    inter.i1 = i;
    inter.i2 = j;

    std::cout << "i: " << i << std::endl;
    std::cout << "j: " << j << std::endl;
    std::cout << "inter: " << inter << std::endl;

    if (!std::isnan(inter.point.x) && !std::isnan(inter.point.y)) {
      intersections.push_back(inter);
    }

    if (p1[i+1].y < p2[j+1].y)
      i++;
    else if (p2[j+1].y < p1[i+1].y)
      j++;
    else
      i++;
  }
}

/*Computes the intersection points between the left half of the first polygon
 and the right half of the second polygon*/
void computeLeftRightIntersection(const Polygon& p1, std::pair<int, int> tb1,
          const Polygon& p2, std::pair<int, int> tb2,
          std::vector<IntersectionPoint>& intersections) {
 // TODO
  std::cout << std::endl;
  std::cout << "##### LEFT-RIGHT #####" << std::endl;

  IntersectionPoint inter;
  int i = tb1.first;
  int j = tb2.first;
  int p1bot = tb1.second;
  int p2bot = tb2.second;

  while (true) {
    if ((p1[i].x == p1[p1bot].x && p1[i].y == p1[p1bot].y) || (p2[j].x == p2[p2bot].x && p2[j].y == p2[p2bot].y)) { break; }
    if (i == p1.size()) { i = 0; }
    if (j == p2.size()) { j = 0; }

    inter.point = Line(p1[i].x,p1[i].y,p1[i+1].x,p1[i+1].y).intersection(Line(p2[j].x,p2[j].y,p2[j-1].x,p2[j-1].y));
    inter.i1 = i;
    inter.i2 = j;

    std::cout << "i: " << i << std::endl;
    std::cout << "j: " << j << std::endl;
    std::cout << "inter: " << inter << std::endl;

    if (!std::isnan(inter.point.x) && !std::isnan(inter.point.y)) {
      intersections.push_back(inter);
    }

    if (p1[i+1].y > p2[j-1].y)
      i++;
    else if (p2[j-1].y > p1[i+1].y)
      j--;
    else
      i++;
  }
}

/*Computes the intersection points between the right half of the first polygon
 and the left half of the second polygon*/
void computeRightLeftIntersection(const Polygon& p1, std::pair<int, int> tb1,
          const Polygon& p2, std::pair<int, int> tb2,
          std::vector<IntersectionPoint>& intersections) {
  // TODO
  std::cout << std::endl;
  std::cout << "##### RIGHT-LEFT #####" << std::endl;

  IntersectionPoint inter;
  int i = tb1.first;
  int j = tb2.first;
  int p1bot = tb1.second;
  int p2bot = tb2.second;

  while (true) {
    if ((p1[i].x == p1[p1bot].x && p1[i].y == p1[p1bot].y) || (p2[j].x == p2[p2bot].x && p2[j].y == p2[p2bot].y)) { break; }
    if (i == p1.size()) { i = 0; }
    if (j == p2.size()) { j = 0; }

    inter.point = Line(p1[i].x,p1[i].y,p1[i-1].x,p1[i-1].y).intersection(Line(p2[j].x,p2[j].y,p2[j+1].x,p2[j+1].y));
    inter.i1 = i;
    inter.i2 = j;

    std::cout << "i: " << i << std::endl;
    std::cout << "j: " << j << std::endl;
    std::cout << "inter: " << inter << std::endl;

    if (!std::isnan(inter.point.x) && !std::isnan(inter.point.y)) {
      intersections.push_back(inter);
    }

    if (p1[i-1].y > p2[j+1].y)
      i--;
    else if (p2[j+1].y > p1[i-1].y)
      j++;
    else
      i--;
  }
}

/**
 * Find all the intersection points between two convex polygons
 */
void findIntersectionPoints(const Polygon& p1, const Polygon& p2,
      std::vector<IntersectionPoint>& intersections) {
	// intersection points already calculated from above and are in the list.
}

int main() {

  // Example code for the intersection between two line segments
//  Point i = Line(2,0,0,1).intersection(Line(0,0,1,4));
//  std::cout << i << std::endl;

  // Example code for creating a polygon
  Polygon p1;
  p1.push_back(Point(2, 2));
  p1.push_back(Point(6, 1));
  p1.push_back(Point(7, 4));
  p1.push_back(Point(3, 6));
  // Example code for finding the top and bottom points of a polygon
  std::cout << "Top/Bottom points for p1 are " << findTopAndBottomPoints(p1) << std::endl;

  // Example code for creating a second polygon
  Polygon p2;
  p2.push_back(Point(4,1));
  p2.push_back(Point(5,6));
  p2.push_back(Point(1,4));
  std::cout << "Top/Bottom points for p2 are " << findTopAndBottomPoints(p2) << std::endl;

  // Example code for finding the intersection between two convex polygons
  std::vector<IntersectionPoint> intersections;
  computeLeftLeftIntersection(p1, findTopAndBottomPoints(p1), p2, findTopAndBottomPoints(p2), intersections);
  computeRightRightIntersection(p1, findTopAndBottomPoints(p1), p2, findTopAndBottomPoints(p2), intersections);
  computeLeftRightIntersection(p1, findTopAndBottomPoints(p1), p2, findTopAndBottomPoints(p2), intersections);
  computeRightLeftIntersection(p1, findTopAndBottomPoints(p1), p2, findTopAndBottomPoints(p2), intersections);
  findIntersectionPoints(p1, p2, intersections);
  std::cout << std::endl;
  std::cout << intersections << std::endl;
  std::cout << "Done" << std::endl;
  return 0;
}
