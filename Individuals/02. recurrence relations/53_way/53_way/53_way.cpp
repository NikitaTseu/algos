#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define MAX 2000000007

ifstream fin("input.txt");
ofstream fout("output.txt");

int n, m;

vector < vector <int> > a(203);
vector < vector <long long int> > dp(203);

int main()
{
	fin >> n >> m;
	for (int i = 1; i < n + 1; i++) {
		vector<int> tmpVect(1003);
		vector<long long int> d(1003, MAX);
		tmpVect[0] = MAX;
		for (int j = 1; j < m + 1; j++) {
			fin >> tmpVect[j];
		}
		tmpVect[n + 1] = MAX;

		dp[i] = d;
		a[i] = tmpVect;
	}
	vector<int> tmpVect(1003, MAX);
	a[0] = tmpVect;
	a[n + 1] = tmpVect;

	vector<long long int> d(1003, MAX);
	dp[0] = d;
	dp[n + 1] = d;

	dp[1][1] = a[1][1];
	for (int i = 2; i <= m; i++) {
		dp[1][i] = MAX;
	}

	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j] = a[i][j] + min(min(dp[i - 1][j], dp[i - 1][j - 1]), dp[i - 1][j + 1]);
		}
	}

	if (m > n) {
		fout << -1;
	}
	else {
		fout << dp[n][m];
	}
    return 0;
}

