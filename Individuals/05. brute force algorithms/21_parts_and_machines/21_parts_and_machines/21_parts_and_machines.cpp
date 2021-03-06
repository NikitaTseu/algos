#include "stdafx.h"
#include <fstream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

#define MAX 2000000007

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int n = 20, m = 20;
int record = MAX;

struct Node;

int c = 0;

vector <int> cost;
vector <int> ans;
queue <Node*> q;

struct Node {
	vector <int> vect;
	vector <Node*> children;
	Node* father;
	int level, groups;

	Node() {
		level = 0;
		groups = 0;
		father = NULL;
		vect.resize(n);
		for (int i = 0; i < n; i++) {
			vect[i] = -1;
		}
	}

	Node(Node* f) {
		father = f;
		vect = f->vect;
		level = f->level + 1;
		groups = f->groups;
	}

	int getTime() {
		vector<int> time(m, 0);
		for (int i = 0; i < n; i++) {
			if (vect[i] != -1) {
				time[vect[i]] += cost[i];
			}
		}
		int maxTime = -1;
		for (int i = 0; i < m; i++) {
			if (time[i] > maxTime) {
				maxTime = time[i];
			}
		}
		return maxTime;
	}

	bool perspective() {
		return getTime() <= record;
	}

	void generateChildren() {
		if (this->perspective()) {
			if (level == n) {
				record = getTime();
				ans = vect;
			}
			else {
				for (int i = 0; i <= groups; i++) {
					children.push_back(new Node(this));
					children[i]->vect[level] = i;
					if (i == groups && groups < m - 1) {
						children[i]->groups++;
					}
					q.push(children[i]);
				}
			}
		}
	}
};

int getRecord() {
	sort(cost.begin(), cost.end(), greater<int>{});
	vector<int> mach(m, 0);
	for (int i = 0; i < n; i++) {
		int imin = 0;
		for (int j = 0; j < m; j++) {
			if (mach[j] < mach[imin]) {
				imin = j;
			}
		}
		mach[imin] += cost[i];
	}
	int rec = -1;
	for (int i = 0; i < m; i++) {
		if (mach[i] > rec) {
			rec = mach[i];
		}
	}

	return rec;
}

int main()
{
	// reading data
	fin >> n >> m;
	cost.resize(n);
	for (int i = 0; i < n; i++){
		fin >> cost[i];
	}

	// get first record
	record = getRecord();

	// brute force
	Node root = Node();
	q.push(&root);
	while (!q.empty()) {
		q.front()->generateChildren();
		q.pop();
	}

	fout << record << endl;
	for (int i = 0; i < m; i++) {
		bool first = true;
		for (int j = 0; j < n; j++) {
			if (ans[j] == i) {
				if (first) {
					first = false;
					fout << cost[j];
				}
				else {
					fout << " " << cost[j];
				}
			}
		}
		if (first) {
			fout << -1;
		}
		fout << endl;
	}
    return 0;
}

