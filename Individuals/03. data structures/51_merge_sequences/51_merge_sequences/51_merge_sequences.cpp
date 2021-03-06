#include "stdafx.h"
#include "stdio.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

#define MAX 2000000007
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

//ifstream fin("input.txt");
//ofstream fout("output.txt");

FILE *file = fopen("input.txt", "r");
FILE *out = fopen("output.txt", "w");

struct Sq {
	vector <int> v;
	int x;
	Sq() :v(vector<int>(1007, MAX)), x(0) {};
};

struct Elem {
	int ind, val;
	Elem() : ind(-1), val(MAX) {};
	Elem(int a, int b) : ind(a), val(b) {};
};

const bool operator < (const Elem &s1, const Elem &s2) {
	return s1.val < s2.val;
}

const bool operator > (const Elem &s1, const Elem &s2) {
	return s1.val > s2.val;
}

int n, m;
vector < Elem > tree(1007);
vector <Sq> dat(1007);

void sift(int j) {
	if (j <= n / 2 && tree[j] > min(tree[j * 2], tree[j * 2 + 1])) {

		if (tree[j * 2] < tree[j * 2 + 1]) {
			swap(tree[j * 2], tree[j]);
			j = j * 2;
			sift(j);
		}
		else {
			swap(tree[j * 2 + 1], tree[j]);
			j = j * 2 + 1;
			sift(j);
		}
	}
}

int main()
{
	fscanf(file, "%d", &n);
	fscanf(file, "%d", &m);

	//creating binary heap O(n)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fscanf(file, "%d", &dat[i].v[j]);
		}
		tree[i + 1] = Elem(i, dat[i].v[0]);
	}
	tree[n + 1] = Elem(n, MAX);
	for (int i = n / 2; i >= 1; i--) {
		int j = i;
		sift(j);
	}

	fclose(file);

	//working with binary heap
	for (int i = 0; i < m*n; i++) {
		if (tree[1].val != MAX) {
			if (i != 0) {
				fprintf(out, " %d", tree[1].val);
			}
			else {
				fprintf(out, "%d", tree[1].val);
			}
			dat[tree[1].ind].x++;
			tree[1].val = dat[tree[1].ind].v[dat[tree[1].ind].x];
		}
		sift(1);
	}
	return 0;
}

// creating binary heap --> O(n)
// modify key (mn times) --> mn * O(log n)
// total --> O(mn * log n)