#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX 100007;

ifstream fin("input.txt");
ofstream fout("output.txt");

int n, N, ans = 0;
vector<int> tree(1000000);

struct Player {
	int x, y, z;
	Player() :x(-1), y(-1), z(-1) {};
	Player(int x, int y, int z) :x(x), y(y), z(z) {};
};

bool predx(Player& p1, Player& p2){
	return(p1.x < p2.x);
}

void treeAdd(int i, int val) {
	tree[N / 2 + i] = val;
	int index = (N / 2 + i) / 2;
	while (index >= 1) {
		tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
		index /= 2;
	}
}

//minimum on [l,r]
int prefixMin(int l, int r, int i, int L, int R) {
	if (r < L || l > R) {
		return MAX;
	}
	else {
		if (L >= l && R <= r) {
			return tree[i];
		}
		else {
			return min(prefixMin(l, r, 2 * i, L, (L + R) / 2), prefixMin(l, r, 2 * i + 1, (L + R) / 2 + 1, R));
		}
	}
}

int main()
{
	//reading data
	fin >> n;
	vector<Player> v(n);
	for (int i = 0; i < n; i++) {
		fin >> v[i].x >> v[i].y >> v[i].z;
	}
	sort(v.begin(), v.end(), predx);

	//creating segment tree
	N = 1;
	while (N < n) {
		N *= 2;
	}
	N *= 2;
	for (int i = 0; i < N; i++) {
		tree[i] = MAX;
	}

	//working with segment tree
	for (int i = 0; i < n; i++) {
		if (v[i].z < prefixMin(1, v[i].y - 1, 1, 1, N/2)) {
			ans++;
		}
		treeAdd(v[i].y - 1, v[i].z);
	}

	fout << ans;
    return 0;
}

