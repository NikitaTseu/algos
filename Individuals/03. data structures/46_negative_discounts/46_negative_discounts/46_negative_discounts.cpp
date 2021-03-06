#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct Shop {
	long long int price;
	int d;

	Shop() : price(200000007), d(200000007) {};
	Shop(long long int p, long long int d) : price(p), d(d) {};

};

const bool operator < (const Shop &s1, const Shop &s2) {
	if (s1.price != s2.price) {
		return s1.price < s2.price;
	}
	else {
		return s1.d < s2.d;
	}
}

const bool operator > (const Shop &s1, const Shop &s2) {
	if (s1.price != s2.price) {
		return s1.price > s2.price;
	}
	else {
		return s1.d > s2.d;
	}
}

int n, k;
vector <Shop> tree(200007);

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
	long long int a = 0, sum = 0;
	fin >> n >> k;

	//creating binary heap O(n)
	for (int i = 1; i <= n; i++) {
		fin >> tree[i].price >> tree[i].d;
	}
	for (int i = n / 2; i >= 1; i--) {
		int j = i;
		sift(j);
	}

	//solving the problem
	while (a != k) {
		a++;
		sum += tree[1].price;
		tree[1].price += tree[1].d;
		sift(1);
	}
	
	fout << sum;
    return 0;
}

