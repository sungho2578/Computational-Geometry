/*
	UCR Spring 2019
	CS 133 Lab 2 - Linear Algebra
	Sungho Ahn, 862026328
*/

#include <iostream>
#include <math.h>
using namespace std;


// Point class with 2 point attributes x and y
class Point
{
	public:
		double x, y;

		void set_point(double x_coord, double y_coord)
		{
			x = x_coord;
			y = y_coord;
		}
};
typedef Point Vector; // Synonym


// Cross Product Implementation
double CrossProduct(Vector v1, Vector v2)
{
	return ((v1.x * v2.y) - (v2.x * v1.y));
}


// Dot Product Implementation
double DotProduct(Vector v1, Vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y));
}


// Collinear Implementation
bool isCollinear(Point p1, Point p2, Point p3)
{
	int sum = (p1.x * (p2.y - p3.y)) + (p2.x * (p3.y - p1.y)) + (p3.x * (p1.y - p2.y));

	if (sum == 0) { return true; }
	else return false;
}


// Relate Implementation
int Relate(Point p1, Point p2, Point p3)
{
	p2.x -= p1.x;
	p2.y -= p1.y;
	p3.x -= p1.x;
	p3.y -= p1.y;

	int direction = p2.x * p3.y - p2.y * p3.x;
	if (direction > 0) { return 1; }
	else if (direction < 0) { return -1; }
	return 0;
}


// Intersection Implementation
int Intersection(Point p1, Point p2, Point p3, Point p4)
{
	int result;
	bool isParallel;
	double m = (p2.y - p1.y) / (p2.x - p1.x);
	double m2 = (p4.y - p3.y) / (p4.x - p3.x);
	if (m == m2){
		isParallel = true;
	}
	else {
		isParallel = false;
	}

	// Case 1
	bool x_compare = (min(p1.x, p2.x) == min(p3.x, p4.x));
	if (isParallel && !x_compare){
		result = 1;
	}

	// Case 2
	double dist = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) * 1.0);
	double dist2 = sqrt(pow(p4.x - p3.x, 2) + pow(p4.y - p3.y, 2) * 1.0);
	bool dist_compare = (dist == dist2);
	if (isParallel && dist_compare){
		result = 2;
	}

	// Case 3
	if (!isParallel){
		result = 3;
	}

	return result;
}


int main()
{
	// ======== Cross & Dot Product Tests ========
	Vector v1;
	v1.set_point(1, -1);

	Vector v2;
	v2.set_point(2, 3);

	cout << endl;
	cout << ":: Vectors set as: v1(" << v1.x << ", " << v1.y << "), v2(" << v2.x << ", " << v2.y << ") ::" << endl;
        cout << "> Cross product result: " << CrossProduct(v1, v2) << endl;
        cout << "> Dot product result: " << DotProduct(v1, v2) << endl << endl;


	// ======== Collinear & Relate Tests ========
	Point p1;
	p1.set_point(-5, 7);

	Point p2;
	p2.set_point(-4, 5);

	Point p3;
	p3.set_point(1, -5);

	cout << ":: Points set as: p1(" << p1.x << ", " << p1.y << "), p2(" << p2.x << ", " << p2.y << "), p3(" << p3.x << ", " << p3.y << ") ::" << endl;
	if (isCollinear(p1, p2, p3) == true) {
		cout << "> Collinear result: Collinear" << endl;
	}
	else cout << "> Collinear result: Not Collinear" << endl;
	if (Relate(p1, p2, p3) > 0) {
	cout << "> Relate result: +ve" << endl << endl;
	}
	else if (Relate(p1, p2, p3) < 0){
	cout << "> Relate result: -ve" << endl << endl;
	}
	else cout << "> Relate result: 0" << endl << endl;

	// ======== Intersection Test ========
	Point p4;
	p1.set_point(2, 4);
	p2.set_point(4, 8);
	p3.set_point(1, 7);
	p4.set_point(3, 11);

	cout << ":: Points set as: p1(" << p1.x << ", " << p1.y << "), p2(" << p2.x << ", " << p2.y << "), p3(" << p3.x << ", " << p3.y << "), p4(" << p4.x << ", " << p4.y << ") ::" << endl;
	cout << "> Intersection result: " << Intersection(p1, p2, p3, p4) << endl << endl;

	return 0;
}
