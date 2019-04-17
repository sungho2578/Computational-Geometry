/*
	UCR Spring 2019
	CS 133 Lab 3 - Convex Hull
	Sungho Ahn, 862026328
*/

#include <iostream>
#include <stdlib.h>
#include <stack>
using namespace std;


// Point class with 2 point attributes x and y
class Point
{
	public:
	    double x, y;
};

Point p0;


// Helper function that returns next to top element in stack
Point nextToTop(stack<Point> &S) {
	Point p = S.top();
	S.pop();
	Point res = S.top();
	S.push(p);

	return res;
}


// Helper function that returns reversed stack
void reverseStack(stack<Point> &S) {
	stack<Point> tempS;
	Point temp;

	while (!S.empty()) {
		temp = S.top();
		S.pop();
		tempS.push(temp);
	}

	S = tempS;
	return;
}


// Helper function that swaps two points
void Swap(Point &p1, Point &p2) {
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}


// Helper function that returns distance square between two points
int DistSquare(Point p1, Point p2) {
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}


// Helper function that returns sorted direction or orientation (Col, CW, CCW)
int Direction(Point p1, Point p2, Point p3) {
	int dir = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);

	if (dir == 0) return 0;  // return 0 if colinear
	if (dir > 0) return 1;
	else return 2; // return 1 if CW, return 2 if CCW
}

// Helper function for qsort() to sort an array based on first point
int Compare(const void *sp1, const void *sp2) {
	Point *p1 = (Point *) sp1;
	Point *p2 = (Point *) sp2;

	int res = Direction(p0, *p1, *p2);
	if (res == 0)
		if (DistSquare(p0, *p2) >= DistSquare(p0, *p1))
			return -1;
		else return 1;

	if (res == 2) return -1;
	else return 1;
}

// Implements convex hull using Graham Scan Algorithm
void ConvexHull(Point Points[], int points) {

	// Find bottom-most point
	int bottomY = Points[0].y;
	int min = 0;
	for (int i = 1; i < points; i++) {
		int y = Points[i].y;

		// If two or more bottom-most points, find one with less x-value
		if ((y < bottomY) || (bottomY == y && Points[i].x < Points[min].x))
			bottomY = Points[i].y, min = i;
	}

	// Place the bottom-most point in the first
	Swap(Points[0], Points[min]);

	// Sort n-1 points
	p0 = Points[0];
	qsort(&Points[1], points-1, sizeof(Point), Compare);

	int mod_size = 1; // Size of modified array
	for (int i = 1; i < points; i++) {
		while (i < points-1 && Direction(p0, Points[i], Points[i+1]) == 0)
			i++;

		Points[mod_size] = Points[i];
		mod_size++;
	}

	// If mod array has less than 3 points, convex hull is not computable
	if (mod_size < 3) return;

	// Push first three points in stack
	stack<Point> S;
	S.push(Points[0]);
	S.push(Points[1]);
	S.push(Points[2]);

	for (int i = 3; i < mod_size; i++) {
		while (Direction(nextToTop(S), S.top(), Points[i]) != 2)
			S.pop();
			S.push(Points[i]);
	}

	// Prints the output points in stack in CCW order
	reverseStack(S);
	while (!S.empty()) {
		Point p = S.top();
		cout << "(" << p.x << ", " << p.y <<")" << endl;
		S.pop();
	}
}


int main() {
	// Set points here for test cases
	Point Points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
			{0, 0}, {3, 1}, {4, 4}, {0, 3}};

	int num_points = sizeof(Points) / sizeof(Points[0]);
	ConvexHull(Points, num_points);

	return 0;
}
