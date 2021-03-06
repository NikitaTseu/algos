#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int c, m;

int h(int x, int i) {
	return ((x % m) + i * c) % m;
}

int main()
{
	int n;
	fin >> m >> c >> n;
	vector<int> a(m);
	vector<int> keys(n);

	for (int i = 0; i < n; i++) {
		fin >> keys[i];
	}

	for (int i = 0; i < m; i++) {
		a[i] = -1;
	}

	for (int j = 0; j < n; j++) {
		int i = 0;
		while (a[h(keys[j], i)] != -1 && a[h(keys[j], i)] != keys[j]) {
			i++;
		}
		if (a[h(keys[j], i)] != keys[j]) {
			a[h(keys[j], i)] = keys[j];
		}
	}

	for (int i = 0; i < m - 1; i++) {
		fout << a[i] << " ";
	}
	fout << a[m - 1];
	return 0;
}

