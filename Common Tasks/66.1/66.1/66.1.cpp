#include "stdafx.h"
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
	int n;
	int u, v;

	fin >> n;

	int* p = new int[n];
	for (int i = 0; i < n; i++) {
		p[i] = 0;
	}

	for (int i = 0; i < n-1; i++) {
		fin >> u >> v;
		p[v - 1] = u;
	}

	for (int i = 0; i < n; i++) {
		fout << p[i] << endl;
	}
	return 0;
}

