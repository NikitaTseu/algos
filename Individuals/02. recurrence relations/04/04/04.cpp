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
double** dp;

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
		dp[p % n][k % n] = 0;
		return 0;
	}
	else {
		if (k == 2) {
			dp[p % n][k % n] = d(a[p % n], a[(p + k) % n]);
			return d(a[p % n], a[(p + k) % n]);
		}
		else {
			double smin = 2000000000;
			for (int i = p + 1; i < p + k; i++) {
				double s1, s2;

				if (dp[p % n][(i - p) % n] != -1) {
					s1 = dp[p % n][(i - p) % n];
				}
				else {
					s1 = s(a, p, i - p);
				}

				if (dp[i % n][(p + k - i) % n] != -1) {
					s2 = dp[i % n][(p + k - i) % n];
				}
				else {
					s2 = s(a, i, p + k - i);
				}

				smin = min(smin, s1 + s2);
			}
			dp[p % n][k % n] = d(a[p % n], a[(p + k) % n]) + smin;
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

	dp = new double*[n];
	for (int i = 0; i < n; i++) {
		dp[i] = new double[n];
		for (int j = 0; j < n; j++) {
			dp[i][j] = -1;
		}
	}

	double smin = 2000000000;
	for (int p = 0; p < n; p++) {
		smin = min(smin, s(a, p, n - 2));
		//cout << smin << endl;
	}
	//cout << endl;
	/*for (int p = 0; p < n; p++) {
		for (int k = 0; k < n; k++) {
			cout << round(dp[p][k] * 100) / 100 << " ";
		}
		cout << endl;
	}*/
	//cout << endl << endl;
	cout << round(smin * 100) / 100 << endl;
	return 0;
}