#include "stdafx.h"
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
	long long int n;
	fin >> n;

	vector<int> v;
	
	while (n > 0) {
		long long int max = 1;
		int maxh = 0;
		while (max * 2 <= n) {
			max *= 2;
			maxh++;
		}
		v.push_back(maxh);
		n -= max;
	}
	
	sort(v.begin(), v.end());

	for (int i = 0; i < v.size(); i++) {
		fout << v[i] << endl;
	}
	return 0;
}

