#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int n;

struct Point {
	int x, y;

	Point() {
		x = 0;
		y = 0;
	}

	Point(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

const bool operator == (const Point &p1, const Point &p2)
{
	if ((p1.x == p2.x) && (p1.y == p2.y)) {
		return true;
	}
	else {
		return false;
	}
}

double d(Point p1, Point p2) {
	if (p1 == p2) {
		return 0;
	}
	else {
		return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
	}
}

double s(vector<Point> a, int p, int k) {
	if (k == 0 || k == 1) {
		return 0;
	}
	else {
		if (k == 2) {
			return d(a[p % n], a[(p + k) % n]);
		}
		else {
			double smin = 2000000000;
			for (int i = p + 1; i < p + k - 1; i++) {
				smin = min(smin, s(a, p, i - p) + s(a, i, k - i));
			}
			return d(a[p % n], a[(p + k) % n]) + smin;
		}
	}
}

int main()
{
	fin >> n;
	vector<Point> a(n);
	for (int i = 0; i < n; i++) {
		fin >> a[i].x >> a[i].y;
	}

	double smin = 2000000000;
	for (int p = 0; p < n; p++) {
		smin = min(smin, s(a, p, n - 1));
	}
	cout << setprecision(4) << smin*2 << endl;
	return 0;
}