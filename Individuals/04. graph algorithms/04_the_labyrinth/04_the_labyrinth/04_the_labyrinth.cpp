#include "stdafx.h"
#include <fstream>
#include <vector>
#include <queue>

#define MAX 2000000007

using namespace std;

ifstream fin("input.txt"); 
ofstream fout("output.txt");

int n, p, k;
int mf = 0;

vector< vector<int> > a(210);
vector< vector<int> > b(210);
vector< vector<int> > af(210);
vector< vector<int> > bf(210);

vector<int> in(105, 0), out(105, 0);

vector <bool> used;
vector <int> pr;

int backTrack() {
	int i = 2 * n + 1;
	int minf = MAX;
	while (i != 0) {
		if (af[pr[i]][i] > 0 && minf > af[pr[i]][i]) {
			minf = af[pr[i]][i];
		}
		if (bf[pr[i]][i] > 0 && minf > bf[pr[i]][i]) {
			minf = bf[pr[i]][i];
		}
		i = pr[i];
	}
	i = 2 * n + 1;
	while (i != 0) {
		if (af[pr[i]][i] > 0) {
			af[pr[i]][i] -= minf;
			bf[i][pr[i]] += minf;
		}
		if (bf[pr[i]][i] > 0) {
			bf[pr[i]][i] -= minf;
			af[i][pr[i]] += minf;
		}
		i = pr[i];
	}
	return minf;
}

int func() {
	used = vector <bool> (210, false);
	pr = vector <int> (210, -1000);
	queue<int> q;

	q.push(0);
	used[0] = true;

	while (!q.empty()) {
		for (int j = 0; j <= 2 * n + 1; j++) {
			if ((af[q.front()][j] > 0 || bf[q.front()][j] > 0) && !used[j]) {
				used[j] = true;
				q.push(j);
				pr[j] = q.front();
				if (j == 2 * n + 1) {
					return backTrack();
				}
			}
		}
		q.pop();
	}

	return 0;
}


int main()
{
	fin >> n >> p >> k;

	a[0] = vector <int> (210, 0);
	b[0] = vector <int>(210, 0);
	a[2 * n + 1] = vector <int>(210, 0);
	b[2 * n + 1] = vector <int>(210, 0);
	for (int i = 1; i <= n; i++) {
		vector <int> tmp(210, 0);
		for (int j = 1; j <= n; j++) {
			fin >> tmp[j];
		}
		a[i] = tmp;
		b[i] = vector <int>(210, 0);
		b[i + n] = vector <int>(210, 0);
		a[i + n] = vector <int>(210, 0);
	}
	for (int i = 0; i < p; i++) {
		int tmp;
		fin >> tmp;
		in[tmp] = 1;
	}
	for (int i = 0; i < k; i++) {
		int tmp;
		fin >> tmp;
		out[tmp] = 1;
	}

	for (int i = 1; i <= n; i++) {
		a[i][i + n] = 1;
		for (int j = 1; j <= n; j++) {
			if (a[i][j] == 1) {
				a[i][j] = 0;
				a[i + n][j] = 1;
				if (in[i] == 1) {
					a[0][i]++;
				}
				if(out[i] == 1) {
					a[i + n][2 * n + 1]++;
				}
			}
		}
	}

	af = a;
	bf = b;

	for (int i = 0; i <= 2 * n + 1; i++) {
		for (int j = 0; j <= 2 * n + 1; j++) {
			if (a[i][j] > 0) {
				b[j][i] = a[i][j];
			}
		}
	}

	while (true) {
		int d = func();
		mf += d;
		if (d == 0) {
			fout << mf;
			return 0;
		}
	}
	
    return 0;
}

