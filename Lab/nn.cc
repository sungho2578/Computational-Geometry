/*
	UCR Spring 2019
	CS 133 Lab 5 - Line Segment Intersection
	Sungho Ahn, 862026328
*/

#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <cmath>
#include <stdio.h>

struct Point {
    double x, y;

    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}

    Point operator+(const Point& p2) const {
        return Point(x + p2.x, y + p2.y);
    }

    Point operator-(const Point& p2) const {
        return Point(x - p2.x, y - p2.y);
    }

    bool operator==(const Point& p2) const {
        return x == p2.x && y == p2.y;
    }

    bool operator!=(const Point& p2) const {
        return x != p2.x || y != p2.y;
    }

    const Point& operator-=(const Point& p2) {
        x -= p2.x; y -= p2.y;
        return *this;
    }

    const Point& operator+=(const Point& p2) {
        x += p2.x; y += p2.y;
        return *this;
    }
};

typedef Point Vector;
typedef std::pair<Point,Point> Line;

double crossProduct(const Vector& v1, const Vector& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

double dotProduct(const Vector& v1, const Vector& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

bool isCollinear(const Point& p1, const Point& p2, const Point& p3) {
    return crossProduct(p2 - p1, p3 - p1) == 0.0;
}

std::vector<std::pair<Line,Line> > lineSegmentIntersection(const std::vector<Line>& R, const std::vector<Line>& S) {
  std::vector<std::pair<Line,Line> > intersections;
  // TODO compute intersections
  return intersections;
}

int main() {
    return 0;
}
