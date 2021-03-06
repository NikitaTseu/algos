#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("report.in");
ofstream fout("report.out");

int main()
{
	int n;
	fin >> n;

	vector<int> a(n);
	vector<int> arev(n);
	for (int i = 0; i < n; i++) {
		fin >> arev[i];
	}
	a = arev;
	reverse(arev.begin(), arev.end());

	vector <int> increase(n+1);
	vector <int> p1(n);
	increase[0] = -1000000;
	for (int i = 1; i <= n; i++) {
		increase[i] = 1000000;
	}

	vector <int> decrease(n + 1);
	vector <int> p2(n);
	decrease[0] = -1000000;
	for (int i = 1; i <= n; i++) {
		decrease[i] = 1000000;
	}

	vector <int> length(n);
	for (int i = 0; i < n; i++) {
		length[i] = 0;
	}
	int l = 0;
	int ik = 0;
	vector <int> path;

	if (n > 2) {
		for (int i = 0; i < n; i++) {
			int j = int(upper_bound(increase.begin(), increase.end(), a[i]) - increase.begin());
			if ((i != 0) && (increase[j - 1] < a[i])) {
				if (j > 1) {
					p1[i] = increase[j - 1];
				}
				else {
					p1[i] = -1;
				}
			}
			else {
				if ((i == 0) || (increase[j - 1] > a[i])) {
					p1[i] = -1;
				}
				if ((i != 0) && (increase[j - 1] == a[i])) {
					if (j == 2) {
						p1[i] = -1;
					}
					else {
						p1[i] = *(lower_bound(increase.begin(), increase.end(), a[i]) - 1);
					}
				}
			}
			if (increase[j-1] < a[i]) {
				increase[j] = a[i];
				length[i] += j;
			}
			if (increase[j - 1] == a[i]) {
				length[i] += j - 1;
			}
		}

		for (int i = 0; i < n; i++) {
			int j = int(upper_bound(decrease.begin(), decrease.end(), arev[i]) - decrease.begin());
			if ((i != 0) && (decrease[j - 1] < arev[i])) {
				if (j > 1) {
					p2[n - 1 - i] = decrease[j - 1];
				}
				else {
					p2[n - 1 - i] = -1;
				}
			}
			else {
				if ((i == 0) || (decrease[j - 1] > arev[i])) {
					p2[n - 1 - i] = -1;
				}
				if ((i != 0) && (decrease[j - 1] == arev[i])) {
					if (j == 2) {
						p2[n - 1 - i] = -1;
					}
					else {
						p2[n - 1 - i] = *(lower_bound(decrease.begin(), decrease.end(), arev[i]) - 1);
					}
				}
			}
			if (decrease[j - 1] < arev[i]) {
				decrease[j] = arev[i];
				length[n - 1 - i] = min(length[n - 1 - i], j);
			}
			if (decrease[j - 1] == arev[i]) {
				length[n - 1 - i] = min(length[n - 1 - i], j - 1);
			}
		}

		for (int i = 0; i < n; i++) {
			if (l < length[i]) {
				l = length[i];
				ik = i;
			}
		}

		int pos = ik;
		int c = 1;
		path.push_back(ik + 1);
		int i = ik;
		while (c != l) {
			if (a[i] != p1[pos]) {
				i--;
			}
			else {
				path.push_back(i + 1);
				pos = i;
				c++;
			}
		}
		reverse(path.begin(), path.end());
		path.pop_back();

		pos = ik;
		c = 1;
		path.push_back(ik + 1);
		i = ik;
		while (c != l) {
			if (a[i] != p2[pos]) {
				i++;
			}
			else {
				path.push_back(i + 1);
				pos = i;
				c++;
			}
		}

		cout << l - 1 << endl;
		for (int i = 0; i < path.size() - 1; i++) {
			cout << path[i] << " ";
		}
		cout << path[path.size() - 1];
	}
	else {
		cout << "0" << endl << "1";
	}

	return 0;
}

/*for (int i = 0; i < n; i++) {
	increase[i] = 1;
	p1[i] = -1;
	for (int j = 0; j < i; j++) {
		if ((a[j] < a[i]) && (increase[i] < increase[j] + 1)) {
			increase[i] = increase[j] + 1;
			p1[i] = j;
		}
	}
}

for (int i = n - 1; i >= 0; i--) {
	decrease[i] = 1;
	p2[i] = -1;
	for (int j = n - 1; j > i; j--) {
		if ((a[j] < a[i]) && (decrease[i] < decrease[j] + 1)) {
			decrease[i] = decrease[j] + 1;
			p2[i] = j;
		}
	}
	if (length < min(decrease[i], increase[i])) {
		length = min(decrease[i], increase[i]);
		ik = i;
	}
}

int pos = ik;
int c = 0;
while (c != length) {
	path.push_back(pos + 1);
	pos = p1[pos];
	c++;
}
reverse(path.begin(), path.end());
path.pop_back();

pos = ik;
c = 0;
while (c != length) {
	path.push_back(pos + 1);
	pos = p2[pos];
	c++;
}

cout << length - 1 << endl;
for (int i = 0; i < path.size() - 1; i++) {
	cout << path[i] << " ";
}
cout << path[path.size() - 1];*/