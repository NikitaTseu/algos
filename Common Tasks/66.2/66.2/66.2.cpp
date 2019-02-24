#include "stdafx.h"
#include <fstream>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
	int n;

	fin >> n;

	int** a = new int*[n];
	for (int i = 0; i < n; i++) {
		a[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fin >> a[i][j];
		}
	}

	int* p = new int[n];
	for (int i = 0; i < n; i++) {
		p[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 1) {
				p[j] = i + 1;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		fout << p[i] << endl;
	}
	return 0;
}

