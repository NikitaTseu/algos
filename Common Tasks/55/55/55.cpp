#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
	int n;
	fin >> n;
	vector<int> a(n+1);

	for (int i = 1; i <= n; i++) {
		fin >> a[i];
	}

	for (int i = 1; i <= n; i++) {
		if (2 * i + 1 <= n){
			if (a[2 * i + 1] < a[i]) {
				fout << "No";
				return 0;
			}
		}
		if (2 * i <= n) {
			if (a[2 * i] < a[i]) {
				fout << "No";
				return 0;
			}
		}
	}
	fout << "Yes";
    return 0;
}

