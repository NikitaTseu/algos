#include "stdafx.h"
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#define MAX 2000000007
#define MAXL 922337203685477580
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

FILE *in = fopen("input.txt", "r");
ofstream fout("output.txt");

struct Request {
	int dest, time;

	Request() : dest(-1), time(-1) {};
	Request(int dest, int time) : dest(dest), time(time) {};
};

int n, m, qq;

vector < vector <int> > a(10003);
vector <int> w(10003, MAX);
vector <bool> used(10003, false);

vector <Request> r(5003);


int main()
{
	fscanf(in, "%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int beg, end;
		fscanf(in, "%d%d", &beg, &end);
		a[2 * beg - 2].push_back(2 * end - 1);
		a[2 * end - 1].push_back(2 * beg - 2);
		if (beg != end) {
			a[2 * beg - 1].push_back(2 * end - 2);
			a[2 * end - 2].push_back(2 * beg - 1);
		}
	}

	fscanf(in, "%d", &qq);
	for (int i = 0; i < qq; i++) {
		fscanf(in, "%d%d", &r[i].dest, &r[i].time);
		r[i].dest--;
	}

	int time = 0;
	queue <int> q;
	q.push(0);
	used[0] = true;
	w[0] = time;

	while (!q.empty()) {
		for (int i = 0; i < a[q.front()].size(); i++) {
			int curIndex = a[q.front()][i];
			if (!used[curIndex]) {
				q.push(curIndex);
				used[curIndex] = true;
				w[curIndex] = w[q.front()] + 1;
			}
		}
		q.pop();
	}


	for (int i = 0; i < qq; i++) {
		if (n == 1 && m == 0) {
			if (r[i].time == 0) {
				fout << "Yes" << endl;
			}
			else {
				fout << "No" << endl;
			}
		}
		else {
			if (r[i].time % 2 == 0) {
				if (r[i].time >= w[2 * r[i].dest]) {
					fout << "Yes" << endl;
				}
				else {
					fout << "No" << endl;
				}
			}

			if (r[i].time % 2 == 1) {
				if (r[i].time >= w[2 * r[i].dest + 1]) {
					fout << "Yes" << endl;
				}
				else {
					fout << "No" << endl;
				}
			}
		}
	}

    return 0;
}

