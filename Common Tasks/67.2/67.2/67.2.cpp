#include "stdafx.h"
#include <fstream>
#include <queue>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

int n, time = 1;
int** a;
int* p;
bool* used;

void dfs(int t) {
	used[t] = true;
	p[t] = time;
	time++;
	for (int i = 0; i < n; i++) {
		if (a[t][i] == 1 && !used[i]) {
			dfs(i);
		}
	}
}

int main()
{
	//reading data
	fin >> n;

	a = new int*[n];
	for (int i = 0; i < n; i++) {
		a[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fin >> a[i][j];
		}
	}

	//initializing...
	p = new int[n];
	used = new bool[n];
	for (int i = 0; i < n; i++) {
		p[i] = 0;
		used[i] = false;
	}

	//dfs
	dfs(0);

	for (int i = 0; i < n; i++) {
		if (p[i] == 0) {
			fout << "NO";
			return 0;
		}
	}
	fout << "YES";
	return 0;
}
