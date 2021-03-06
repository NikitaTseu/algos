#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define MAX 2000000007

struct Path {
	int start, end, t1, t2;
	bool used;
	Path() : start(MAX), end(MAX), t1(MAX), t2(MAX), used(true) {};
	Path(int a, int b, int c, int d) : start(a), end(b), t1(c), t2(d), used(false) {};
};

int n, k, a, b, time = MAX;
vector <Path> g(200007);
queue<Path> q;

//ifstream fin("time.in");
//ofstream fout("time.out");

ifstream fin("input1.txt");
ofstream fout("output.txt");

int main()
{
	fin >> n >> a >> b >> k;
	g[0] = Path(a, a, 0, 0);
	for (int i = 1; i <= k; i++) {
		fin >> g[i].start >> g[i].t1 >> g[i].end >> g[i].t2;
		g[i].used = false;
	}

	q.push(g[0]);
	g[0].used = true;
	while (!q.empty()) {
		int i = 1;
		while (i <= k && g[i].start != q.front().end) {
			i++;
		}
		while (i <= k && g[i].start == q.front().end) {
			if (!g[i].used && g[i].t1 >= q.front().t2) {
				g[i].used = true;
				q.push(g[i]);
				if (g[i].end == b && time > g[i].t2) {
					time = g[i].t2;
				}
			}
			i++;
		}
		q.pop();
	}

	if (a == b && time > 0) {
		time = 0;
	}
	fout << time;
    return 0;
}

