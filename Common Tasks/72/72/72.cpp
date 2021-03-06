#include "stdafx.h"
#include <fstream>
#include <vector>
#include <queue>

#define MAX 2000000007
#define MAXL 922337203685477580
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

FILE *in = fopen("input.txt", "r");
ofstream fout("output.txt");

int n, m;

struct Edge {
	int cost, a, b;

	Edge() : cost(MAX), a(-1), b(-1) {};
	Edge(int cost, int a, int b) : cost(cost), a(a), b(b) {};
};

struct Elem {
	int ind;
	long long int prior;

	Elem() : ind(-1), prior(-1 * MAXL) {};
	Elem(int ind, long long int prior) : ind(ind), prior(prior) {};
};

const bool operator < (const Elem &s1, const Elem &s2) {
	return s1.prior > s2.prior;
}
const bool operator > (const Elem &s1, const Elem &s2) {
	return s1.prior < s2.prior;
}

vector <vector<Edge>> g(200007);
vector <long long int> d(200007, MAXL);
priority_queue<Elem> q;
vector<bool> locked(200007, false);

int main()
{
	fscanf(in, "%d", &n);
	fscanf(in, "%d", &m);

	for (int i = 0; i < m; i++) {
		int u, v, cost;
		fscanf(in, "%d", &u);
		fscanf(in, "%d", &v);
		fscanf(in, "%d", &cost);
		g[u - 1].push_back(Edge(cost, u - 1, v - 1));
		g[v - 1].push_back(Edge(cost, v - 1, u - 1));
	}
	fclose(in);

	d[0] = 0;
	q.push(Elem(0, 0));
	while (!q.empty()) {
		if (!locked[q.top().ind]) {
			locked[q.top().ind] = true;
			for (int i = 0; i < g[q.top().ind].size(); i++) {
				if (!locked[g[q.top().ind][i].b] && d[g[q.top().ind][i].b]>(q.top().prior + g[q.top().ind][i].cost)) {
					q.push(Elem(g[q.top().ind][i].b, q.top().prior + g[q.top().ind][i].cost));
					d[g[q.top().ind][i].b] = q.top().prior + g[q.top().ind][i].cost;
				}
			}
		}
		q.pop();
	}

	fout << d[n - 1];
	return 0;
}
