#include "stdafx.h"
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
	int v, r;
	int u1, u2;
	char c;

	fin >> v >> r;

	vector< vector<int>> a;
	for (int i = 0; i < v; i++) {
		vector<int> tmp;
		tmp.push_back(0);
		a.push_back(tmp);
	}
	
	for (int i = 0; i < r; i++) {
		fin >> u1 >> u2;
		a[u1 - 1][0]++;
		a[u2 - 1][0]++;
		a[u1 - 1].push_back(u2);
		a[u2 - 1].push_back(u1);
	}

	for (int i = 0; i < v; i++) {
		for (int j = 0; j < a[i].size() - 1; j++) {
			fout << a[i][j] << " ";
		}
		fout << a[i][a[i].size() - 1] << endl;
	}
	return 0;
}

