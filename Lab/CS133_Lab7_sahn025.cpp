/*
    UCR Spring 2019
    CS 133 Lab 7 - Line Simplification
    Sungho Ahn, 862026328
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef pair<double, double> Point;
typedef vector<Point> Polyline;

// Calculate distance between a point and a line
double Distance(Point &p1, Point &start, Point &end) {
	double dist_x = end.first - start.first;
	double dist_y = end.second - start.second;
	double magnitude = pow(pow(dist_x, 2.0) + pow(dist_y, 2.0), 0.5);

	if (magnitude > 0.0) {
		dist_x = dist_x / magnitude;
		dist_y = dist_y / magnitude;
	}

	double px = p1.first - start.first;
	double py = p1.second - start.second;
	double dot = dist_x * px + dist_y * py;
	double final_x = px - dot * dist_x;
	double final_y = py - dot * dist_y;
	double result = pow(pow(final_x, 2.0) + pow(final_y, 2.0), 0.5);

	return result;
}

// Simplifying a polyline using Douglas-Peucker algorithm and returns a new polyline
Polyline Simplify(Polyline &p, double epsilon) {
	int index = 0;
	int last = p.size() - 1;
	double max_dist = 0.0;

	for (int i = 1; i < last; i++) {	// Find the maximum distanced point from line
		double dist = Distance(p[i], p[0], p[last]);
		if (dist > max_dist) {
			max_dist = dist;
			index = i;
		}
	}

	Polyline result;

	if (max_dist > epsilon)	{	// Do a recursion if max_dist > epsilon for further simplify
		Polyline line1(p.begin(), p.begin() + 1 + index);
		Polyline line2(p.begin() + index, p.end());
		Polyline result1 = Simplify(line1, epsilon);
		Polyline result2 = Simplify(line2, epsilon);

		result.assign(result1.begin(), result1.end() - 1);
		result.insert(result.end(), result2.begin(), result2.end());
	}

	else {	// Else just return first and last point
		result.push_back(p[0]);
		result.push_back(p[last]);
	}

	return result;
}

int main() {
	Polyline p;
	Polyline result;
	double epsilon = 1.0;

	p.push_back(Point(0.0, 0.0));
	p.push_back(Point(1.0, 0.1));
	p.push_back(Point(2.0, -0.1));
	p.push_back(Point(3.0, 5.0));
	p.push_back(Point(4.0, 6.0));
	p.push_back(Point(5.0, 7.0));
	p.push_back(Point(6.0, 8.1));
	p.push_back(Point(7.0, 9.0));
	p.push_back(Point(8.0, 9.0));
	p.push_back(Point(9.0, 9.0));

	result = Simplify(p, epsilon);

	for (int i = 0; i < result.size(); i++) {
		cout << "(" << result[i].first << ", " << result[i].second << ")" << endl;
	}
}
