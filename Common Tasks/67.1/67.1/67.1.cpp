#include "stdafx.h"
#include <fstream>
#include <queue>

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
	bool* used = new bool[n];
	for (int i = 0; i < n; i++) {
		p[i] = 0;
		used[i] = false;
	}

	p[0] = 1;
	int index = 2;

	queue<int> q;
	q.push(0);
	used[0] = true;

	while (!q.empty()) {
		for (int j = 0; j < n; j++) {
			if (a[q.front()][j] == 1 && !used[j]) {
				used[j] = true;
				q.push(j);
				p[j] = index;
				index++;
			}
		}
		q.pop();
		if (q.empty()) {
			for (int i = 0; i < n; i++) {
				if (used[i] == false) {
					q.push(i);
					p[i] = index;
					index++;
					used[i] = true;
					break;
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		fout << p[i] << endl;
	}
	return 0;
}

