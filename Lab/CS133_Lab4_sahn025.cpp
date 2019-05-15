/*
	UCR Spring 2019
	CS 133 Lab 4 - Monotone Chain Algorithm
	Sungho Ahn, 862026328
*/

#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <vector>
#include <stack>
using namespace std;


// Point class with 2 point attributes x and y
class Point {
	public:
		long long int x, y;

	bool operator < (Point p) {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// Implementation of Cross Product
long long int crossProduct(Point pO, Point p1, Point p2)
{
    return (p1.x - pO.x) * (p2.y - pO.y) - (p1.y - pO.y) * (p2.x - pO.x);
}

// Implementation of ConvexHull using Monotone Chain algorithm
vector<Point> ConvexHull(vector<Point> points)
{
    int j = 0;
    int num = points.size();
    vector<Point> result(2*num);

    // If there less than 3 sets of points, return as is
    if (num <= 3)
        return points;

    // Sort points in increasing order
    sort(points.begin(), points.end());

    // Lower Boundary
    for (int i = 0; i < num; ++i) {
        // Check if is part of vector hull and direction
        while (j >= 2 && crossProduct(result[j-2], result[j-1], points[i]) <= 0)
            j--;
        result[j++] = points[i];
    }

    // Upper Boundary
    for (size_t i = num-1, t = j+1; i > 0; --i) {
	// Check if is part of vector hull and direction
        while (j >= t && crossProduct(result[j-2], result[j-1], points[i-1]) <= 0)
            j--;
        result[j++] = points[i-1];
    }

    result.resize(j-1);

    return result;
}

// Driver code
int main()
{
    vector<Point> points;

    // Set points here
    points.push_back({0, 3});
    points.push_back({1, 1});
    points.push_back({2, 2});
    points.push_back({4, 4});
    points.push_back({0, 0});
    points.push_back({1, 2});
    points.push_back({3, 1});
    points.push_back({3, 3});

    vector<Point> result = ConvexHull(points);

    for (int i = 0; i < result.size(); i++)
        cout << "(" << result[i].x << ", " << result[i].y << ")" << endl;

    return 0;
}
