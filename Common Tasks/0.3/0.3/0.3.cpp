#include "stdafx.h"
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
	int s;
	fin >> s;

	int* p = new int[s + 1];
	fin >> p[0] >> p[1];
	for (int i = 0; i < s - 1; i++) {
		int a;
		fin >> a >> p[i + 2];
	}

	int mas[101][101];
	for (int i = 1; i <= s; i++) {
		mas[i][i] = 0;
	}

	for (int l = 2; l <= s; l++) {
		for (int i = 1; i <= s - l + 1; i++) {
			int j = i + l - 1;
			mas[i][j] = 2000000000;
			for (int k = i; k < j; k++) {
				mas[i][j] = min(mas[i][j], mas[i][k] + mas[k+1][j] + p[i-1]*p[k]*p[j]);
			}
		}
	}

	fout << mas[1][s];
	return 0;
}

